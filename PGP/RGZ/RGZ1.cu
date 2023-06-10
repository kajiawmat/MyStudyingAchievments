#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/inner_product.h>
#include <thrust/gather.h>
#include "cublas_v2.h"

#define START_SIZE (1<<5)
#define FINAL_SIZE (1<<10)
#define ITERATIONS (10-9+1)
#define COUNT 10
#define DATA_COUNT (ITERATIONS*ITERATIONS)
#define THREADS_PER_BLOCK (1<<5)

using namespace std;

struct init_functor
{
	float h;
	init_functor(float _h):h(_h) {}
	__device__ float operator()(float x)
	{
		return h*x;
	}
};

__global__ void gMultMats(float* da, float* db, float* dc,long long N, long long M, long long K)
{
        int m=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

        float acc=0.0f;
        for(int k=0;k<K;k++) acc+=da[k+n*K]*db[m+k*M];
        dc[m+n*M]=acc;
}

__global__ void gInit(float* d, int s)
{
        int j=threadIdx.x+blockIdx.x*blockDim.x;
        int i=threadIdx.y+blockIdx.y*blockDim.y;
        int J=blockDim.x*gridDim.x;

        d[j+i*J]=s*(float)((j+i*J)*1.0E-3)+(1-s)*1.0f;
}

void printMatr(float* d, long long N, long long M)
{
        for(long long i=0;i<N;i++)
        {
                for(long long j=0;j<M;j++) printf("%4.2f ",d[j+i*M]);
                printf("\n");
        }
        printf("\n");
}

void printMatr(thrust::host_vector<float> d, long long N, long long M)
{
        for(long long i=0;i<N;i++)
        {
                for(long long j=0;j<M;j++) printf("%4.2f ",d[j+i*M]);
                printf("\n");
        }
        printf("\n");
}

void printResults(float time_cuda[],float time_thrust[],float time_cublas[])
{
        FILE *fp=fopen("Out.csv","w");
        long long N=START_SIZE;
        long long K=START_SIZE;
        long long M=START_SIZE;
        long long index;
        fprintf(fp,"N;K;M;Threads per block;CUDA C;Thrust;CuBlas;\n");
        for(long long i=0;i<ITERATIONS;i++)
        {
                K=START_SIZE;
                for(long long j=0;j<ITERATIONS;j++)
                {
                        index=i*ITERATIONS+j;
                        fprintf(fp,"%lli;%lli;%lli;",N,K,M);
                        fprintf(fp,"%i;",THREADS_PER_BLOCK);
                        fprintf(fp,"%f;",time_cuda[index]/COUNT);
                        fprintf(fp,"%f;",time_thrust[index]/COUNT);
			fprintf(fp,"%f;",time_cublas[index]/COUNT);
			fprintf(fp,"\n");
			K<<=1;
                }
                N<<=1;
        }
	fclose(fp);
}

int main()
{
	float time_cublas[DATA_COUNT];
	float time_thrust[DATA_COUNT];
        float time_cuda[DATA_COUNT];
        long long N=START_SIZE;
        long long K=START_SIZE;
        long long M=START_SIZE;
        float *ha,*hb,*hc,*da,*db,*dc;
	
	init_functor I(1.0E-3);
	thrust::device_vector<long long> dmap;
        thrust::device_vector<float> dVa;
        thrust::device_vector<float> dVb;
	thrust::device_vector<float> dVbT;
        thrust::device_vector<float> dVc;
        thrust::host_vector<float> hVc;
	thrust::device_vector<float>::iterator iterVa;
	thrust::device_vector<float>::iterator iterVbT;
	long long *map;

	const float alpha=1.0;
	const float beta=0.0;	

        cudaEvent_t time_start,time_stop;
        cudaEventCreate(&time_start);
        cudaEventCreate(&time_stop);

        for(long long i=0;i<ITERATIONS;i++)
        {
                K=START_SIZE;
                for(long long j=0;j<ITERATIONS;j++)
                {
                        cudaMalloc((void**)&da,N*K*sizeof(float));
                        cudaMalloc((void**)&db,K*M*sizeof(float));
                        cudaMalloc((void**)&dc,N*M*sizeof(float));
                        gInit<<<dim3(K/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,1);
                        gInit<<<dim3(M/THREADS_PER_BLOCK,K/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(db,0);
                        cudaDeviceSynchronize();
                        cudaEventRecord(time_start,0);
                        for(long long k=0;k<COUNT;k++)
                        {
                                gMultMats<<<dim3(M/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,db,dc,N,M,K);
                                cudaDeviceSynchronize();
                        }
                        cudaEventRecord(time_stop,0);
                        cudaEventSynchronize(time_stop);
                        cudaEventElapsedTime(&(time_cuda[i*ITERATIONS+j]),time_start,time_stop);
			if(i==1 && j==0)
                        {
                        	ha=(float*) malloc(N*K*sizeof(float));
                        	hb=(float*) malloc(K*M*sizeof(float));
                        	hc=(float*) malloc(N*M*sizeof(float));
                        	cudaMemcpy(ha,da,N*K*sizeof(float),cudaMemcpyDeviceToHost);
                        	cudaMemcpy(hb,db,K*M*sizeof(float),cudaMemcpyDeviceToHost);
                        	cudaMemcpy(hc,dc,N*M*sizeof(float),cudaMemcpyDeviceToHost);
                        	printMatr(ha,N,K);
                        	printMatr(hb,K,M);
                        	printMatr(hc,N,M);
                        	free(ha);
                        	free(hb);
                        	free(hc);
                    	}
                        cudaFree(dc);
                        

			dVa=thrust::device_vector<float>(N*K);
                        dVb=thrust::device_vector<float>(K*M);
			dVbT=thrust::device_vector<float>(M*K);
                        dVc=thrust::device_vector<float>(N*M);
                        hVc=thrust::host_vector<float>(N*M);
                        thrust::sequence(thrust::device,dVa.begin(),dVa.end());
                        thrust::transform(dVa.begin(),dVa.end(),dVa.begin(),I);
                        thrust::fill(dVb.begin(),dVb.end(),1.0f);
			map=(long long*)malloc(M*K*sizeof(long long));
			for(long long i0=0;i0<M*K;i0++) map[i0]=(i0%K)*M+(i0/K);
			dmap=thrust::device_vector<long long>(map,map+M*K);
			thrust::gather(dmap.begin(),dmap.end(),dVb.begin(),dVbT.begin());
                        cudaEventRecord(time_start,0);
			for(long long k=0;k<COUNT;k++)
                        {
				iterVa=dVa.begin();
                                for(long long i0=0;i0<N;i0++)
                                {
					iterVbT=dVbT.begin();
                                        for(long long j0=0;j0<M;j0++)
                                        {
                                                dVc[i0*M+j0]=thrust::inner_product(iterVa,iterVa+K,iterVbT,0.0f);
						iterVbT+=K;
                                        }
					iterVa+=K;
                                }
                                hVc=dVc;
                        }
                        cudaEventRecord(time_stop,0);
                        cudaEventSynchronize(time_stop);
                        cudaEventElapsedTime(&(time_thrust[i*ITERATIONS+j]), time_start, time_stop);
                        if(i==1 && j==0)
                        {
                                printMatr(hVc,N,M);
                        }
			free(map);

                        cudaMalloc((void**)&dc,N*M*sizeof(float));
                        cublasHandle_t cublas_handle;
                	cublasCreate(&cublas_handle);
                	cudaEventRecord(time_start,0);
                	for(long long k=0;k<COUNT;k++)
                	{
                	        cublasSgemm(cublas_handle,CUBLAS_OP_N,CUBLAS_OP_N,M,N,K,&alpha,db,M,da,K,&beta,dc,M);
              		}
                	cudaEventRecord(time_stop,0);
                	cudaEventSynchronize(time_stop);
                	cudaEventElapsedTime(&(time_cublas[i*ITERATIONS+j]), time_start, time_stop);
                        cublasDestroy(cublas_handle);
                        if(i==1 && j==0)
                        {
                                hc=(float*) malloc(N*M*sizeof(float));
                                cublasGetMatrix(M,N,sizeof(float),dc,M,hc,M);
                                printMatr(hc,N,M);
                                free(hc);
                        }
                        cudaFree(da);
                        cudaFree(db);
                        cudaFree(dc);
                        K<<=1;
                }
                N<<=1;
        }
        printResults(time_cuda,time_thrust,time_cublas);
        cudaEventDestroy(time_start);
        cudaEventDestroy(time_stop);
}

