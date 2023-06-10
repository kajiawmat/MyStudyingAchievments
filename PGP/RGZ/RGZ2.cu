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
#define FINAL_SIZE (1<<15)
#define ITERATIONS (15-5+1)
#define COUNT 10
#define DATA_COUNT (ITERATIONS)
#define THREADS_PER_BLOCK (1<<5)
#define SH_DIM (THREADS_PER_BLOCK)

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

__global__ void gTranspose(float* da, float* db, int N, int M)
{
        int m=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

        db[n+m*N]=da[m+n*M];
}

__global__ void gTransposeOpt(float* matr, float* matr_t, long long N, long long M)
{
        __shared__ float buffer[SH_DIM][SH_DIM+1];
        int m=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

        buffer[threadIdx.y][threadIdx.x]=matr[m+n*M];
        __syncthreads();

        m=threadIdx.x+blockIdx.y*blockDim.x;
        n=threadIdx.y+blockIdx.x*blockDim.y;
        matr_t[m+n*N]=buffer[threadIdx.x][threadIdx.y];
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

void printResults(float time_cuda[],float time_cuda_opt[],float time_thrust[],float time_cublas[])
{
        FILE *fp=fopen("Out2.csv","w");
        long long N=START_SIZE;
        long long M=START_SIZE;
        long long index;
        fprintf(fp,"N;M;Threads per block;CUDA C;CUDA C opt;Thrust;CuBlas;\n");
        for(long long i=0;i<ITERATIONS;i++)
        {
                index=i;
                fprintf(fp,"%lli;%lli;",N,M);
                fprintf(fp,"%i;",THREADS_PER_BLOCK);
                fprintf(fp,"%f;",time_cuda[index]/COUNT);
		fprintf(fp,"%f;",time_cuda_opt[index]/COUNT);
                fprintf(fp,"%f;",time_thrust[index]/COUNT);
		fprintf(fp,"%f;",time_cublas[index]/COUNT);
		fprintf(fp,"\n");
                N<<=1;
        }
	fclose(fp);
}

int main()
{
	float time_cublas[DATA_COUNT];
	float time_cuda_opt[DATA_COUNT];
	float time_thrust[DATA_COUNT];
        float time_cuda[DATA_COUNT];
        long long N=START_SIZE;
        long long M=START_SIZE;
        float *ha,*hb,*da,*db;
	
	init_functor I(1.0E-3);
	thrust::device_vector<long long> dmap;
        thrust::device_vector<float> dVa;
        thrust::device_vector<float> dVb;
        thrust::host_vector<float> hVb;
	long long *map;

	const float alpha=1.0;
	const float beta=0.0;	

        cudaEvent_t time_start,time_stop;
        cudaEventCreate(&time_start);
        cudaEventCreate(&time_stop);

        for(long long i=0;i<ITERATIONS;i++)
        {
                        cudaMalloc((void**)&da,N*M*sizeof(float));
                        cudaMalloc((void**)&db,M*N*sizeof(float));
                        gInit<<<dim3(M/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,1);
                        cudaDeviceSynchronize();
                        cudaEventRecord(time_start,0);
                        for(long long k=0;k<COUNT;k++)
                        {
                                gTranspose<<<dim3(M/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,db,N,M);
                                cudaDeviceSynchronize();
                        }
                        cudaEventRecord(time_stop,0);
                        cudaEventSynchronize(time_stop);
                        cudaEventElapsedTime(&(time_cuda[i]),time_start,time_stop);
			if(i==1)
                        {
                        	ha=(float*) malloc(N*M*sizeof(float));
                        	hb=(float*) malloc(M*N*sizeof(float));
                        	cudaMemcpy(ha,da,N*M*sizeof(float),cudaMemcpyDeviceToHost);
                        	cudaMemcpy(hb,db,M*N*sizeof(float),cudaMemcpyDeviceToHost);
                        	printMatr(ha,N,M);
                        	printMatr(hb,M,N);
                        	free(ha);
                        	free(hb);
                    	}
                        cudaFree(db);
                        
			cudaMalloc((void**)&db,M*N*sizeof(float));
			cudaDeviceSynchronize();
                        cudaEventRecord(time_start,0);
                        for(long long k=0;k<COUNT;k++)
                        {
                                gTransposeOpt<<<dim3(M/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,db,N,M);
                                cudaDeviceSynchronize();
                        }
                        cudaEventRecord(time_stop,0);
                        cudaEventSynchronize(time_stop);
                        cudaEventElapsedTime(&(time_cuda_opt[i]),time_start,time_stop);
			if(i==1)
                        {
				hb=(float*) malloc(M*N*sizeof(float));
                                cudaMemcpy(hb,db,M*N*sizeof(float),cudaMemcpyDeviceToHost);
                                printMatr(hb,M,N);
				free(hb);
                        }
			cudaFree(db);

			dVa=thrust::device_vector<float>(N*M);
                        dVb=thrust::device_vector<float>(M*N);
                        hVb=thrust::host_vector<float>(N*M);
                        thrust::sequence(thrust::device,dVa.begin(),dVa.end());
                        thrust::transform(dVa.begin(),dVa.end(),dVa.begin(),I);
			map=(long long*)malloc(M*N*sizeof(long long));
			for(long long i0=0;i0<M*N;i0++) map[i0]=(i0%N)*M+(i0/N);
			dmap=thrust::device_vector<long long>(map,map+M*N);
			cudaEventRecord(time_start,0);
			for(long long k=0;k<COUNT;k++) thrust::gather(dmap.begin(),dmap.end(),dVa.begin(),dVb.begin());
                        cudaEventRecord(time_stop,0);
                        cudaEventSynchronize(time_stop);
                        cudaEventElapsedTime(&(time_thrust[i]), time_start, time_stop);
			hVb=dVb;
                        if(i==1)
                        {
                                printMatr(hVb,M,N);
                        }
			free(map);


                        cudaMalloc((void**)&db,M*N*sizeof(float));
                        cublasHandle_t cublas_handle;
                	cublasCreate(&cublas_handle);
                	cudaEventRecord(time_start,0);
                	for(long long k=0;k<COUNT;k++)
                	{
                	        cublasSgeam(cublas_handle,CUBLAS_OP_T,CUBLAS_OP_T,N,M,&alpha,da,M,&beta,da,M,db,N);
              		}
                	cudaEventRecord(time_stop,0);
                	cudaEventSynchronize(time_stop);
                	cudaEventElapsedTime(&(time_cublas[i]), time_start, time_stop);
                        cublasDestroy(cublas_handle);
                        if(i==1)
                        {
                                hb=(float*) malloc(N*M*sizeof(float));
                                cublasGetMatrix(M,N,sizeof(float),db,M,hb,M);
                                printMatr(hb,M,N);
                                free(hb);
                        }
                        cudaFree(da);
                        cudaFree(db);
                	N<<=1;
        }
        printResults(time_cuda,time_cuda_opt,time_thrust,time_cublas);
        cudaEventDestroy(time_start);
        cudaEventDestroy(time_stop);
}

