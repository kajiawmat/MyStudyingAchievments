#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "cublas_v2.h"

using namespace std;

#define MAX 8.0f
#define MIN -8.0f
#define THREADS_PER_BLOCK 32
#define BLOCK_DIM 32

__global__ void gMultMats(float* da, float* db, float* dc,long long N, long long M, long long K)
{
	int n=threadIdx.x+blockIdx.x*blockDim.x;
	int m=threadIdx.y+blockIdx.y*blockDim.y;
	
	float acc=0.0f;
	for(int k=0;k<K;k++) acc+=da[k+m*K]*db[n+k*N];
	dc[n+m*N]=acc;
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

int main()
{
	cudaEvent_t time_start, time_stop;
	cudaEventCreate(&time_start);
    cudaEventCreate(&time_stop);
    float time_result;
    
    float *ha,*hb,*hc,*da,*db,*dc;
    long long N=1<<6;
    long long M=1<<5;
    long long K=1<<5;
    
    for(long long i=0;i<=5;i++)
    {
        ha=(float*) malloc(M*K*sizeof(float));
        hb=(float*) malloc(K*N*sizeof(float));
        hc=(float*) malloc(M*N*sizeof(float));
        cudaMalloc((void**) &da,M*K*sizeof(float));
        cudaMalloc((void**) &db,K*N*sizeof(float));
        cudaMalloc((void**) &dc,M*N*sizeof(float));
        
        gInit<<<dim3(K/THREADS_PER_BLOCK,M/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,1);
        cudaDeviceSynchronize();
        gInit<<<dim3(N/THREADS_PER_BLOCK,K/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(db,0);
        cudaDeviceSynchronize();
        cudaMemcpy(ha,da,M*K*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(hb,db,K*N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaEventRecord(time_start,0);
        gMultMats<<<dim3(N/THREADS_PER_BLOCK,M/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,db,dc,N,M,K);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaDeviceSynchronize();
        cudaMemcpy(hc,dc,M*N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        cudaDeviceSynchronize();
        //printMatr(ha,M,K);
        //printMatr(hb,K,N);
        //printMatr(hc,M,N);
        printf("M=%lli, N=%lli, K=%lli\n",M,N,K);
        printf("Time = %f\n", time_result);
	
	cudaFree(dc);
        cudaMalloc((void**) &dc,M*N*sizeof(float));
        cudaEventRecord(time_start,0);
        cublasHandle_t cublas_handle;
        cublasCreate(&cublas_handle);

        const float alpha=1.0;
        const float beta=0.0;
	cudaEventRecord(time_start,0);
        //cublasSgemm(cublas_handle,CUBLAS_OP_T,CUBLAS_OP_T,M,N,K,
        //&alpha,da,M,db,N,&beta,dc,M);
	cublasSgemm(cublas_handle,CUBLAS_OP_N,CUBLAS_OP_N,N,M,K,
        &alpha,db,N,da,K,&beta,dc,N);
	cudaEventRecord(time_stop,0);
        cublasDestroy(cublas_handle);
        cudaEventSynchronize(time_stop);
        cudaDeviceSynchronize();
        cudaEventElapsedTime(&time_result, time_start, time_stop);
	cublasGetMatrix(N,M,sizeof(float),dc,N,hc,N);
        cudaDeviceSynchronize();
        //printMatr(hc,M,N);
        printf("Time cuBlas = %f\n", time_result);
	
    	K<<=1;
        cudaFree(da);
        cudaFree(db);
        cudaFree(dc);
        free(ha);
        free(hb);
        free(hc);
    }
    
    cudaEventDestroy(time_start);
    cudaEventDestroy(time_stop);
}
