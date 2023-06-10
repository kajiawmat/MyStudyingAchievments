#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/inner_product.h>
#include <thrust/gather.h>
#include <thrust/execution_policy.h>

using namespace std;

#define MAX 8.0f
#define MIN -8.0f
#define ROW_SIZE 32
#define THREADS_PER_BLOCK 32
#define NUM_OF_BLOCKS 32
#define SH_DIM 32

__host__ float rand_f() {
	return ((float)rand()*(MAX-MIN)/RAND_MAX+MIN);
}


__global__ void gTranspote(float* matr, float* matr_t, long long N, long long K)
{
        int k=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

        matr_t[k*N+n]=matr[n*K+k];
}

int main()
{
	cudaEvent_t time_start, time_stop;
	cudaEventCreate(&time_start);
    cudaEventCreate(&time_stop);
    float time_result;
    
    float *ha,*hb,*da,*db;
    long long N=32;
	thrust::host_vector<float> hVa;
	thrust::host_vector<float> hVb;
	thrust::device_vector<float> dVa;
	thrust::device_vector<float> dVb;
	thrust::device_vector<long long> dmap;
	long long map[ROW_SIZE*(N<<4)];
    for(long long i=0;i<5;i++)
    {
        ha=(float*) malloc(ROW_SIZE*N*sizeof(float));
        hb=(float*) malloc(ROW_SIZE*N*sizeof(float));
        cudaMalloc((void**) &da,ROW_SIZE*N*sizeof(float));
        cudaMalloc((void**) &db,ROW_SIZE*N*sizeof(float));
        for(long long j=0;j<N;j++)
        {
            for(long long k=0;k<ROW_SIZE;k++)
            {
           		ha[j*ROW_SIZE+k]=rand_f();
           		printf("%6.2f ",ha[j*ROW_SIZE+k]);
            }
            printf("\n");    
        }
        printf("\n");
        cudaMemcpy(da,ha,ROW_SIZE*N*sizeof(float),cudaMemcpyHostToDevice);
        cudaEventRecord(time_start,0);
        gTranspote<<<dim3(ROW_SIZE/THREADS_PER_BLOCK,N/THREADS_PER_BLOCK),dim3(THREADS_PER_BLOCK,THREADS_PER_BLOCK)>>>(da,db,N,ROW_SIZE);
        cudaDeviceSynchronize();
        cudaMemcpy(hb,db,ROW_SIZE*N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        cudaDeviceSynchronize();
        for(long long j=0;j<ROW_SIZE;j++) 
        {
        	for(long long k=0;k<N;k++) printf("%6.2f ",hb[j*N+k]);
        	printf("\n");
        }
        printf("\n");
        printf("Matrix Size = %lliX%lli\n",ROW_SIZE,N);
        printf("Time = %f\n", time_result);


		for(long long j=0;j<N*ROW_SIZE;j++) map[j]=(j%N)*ROW_SIZE+(j/N);
		hVa=thrust::host_vector<float>(ROW_SIZE*N);
        hVb=thrust::host_vector<float>(ROW_SIZE*N);
        dVa=thrust::device_vector<float>(ROW_SIZE*N);
        dVb=thrust::device_vector<float>(ROW_SIZE*N);
        dmap=thrust::device_vector<long long>(map,map+ROW_SIZE*N);

        thrust::generate(hVa.begin(),hVa.end(),rand_f);
        dVa=hVa;
        for(long long j=0;j<N;j++)
        {
            for(long long k=0;k<ROW_SIZE;k++) printf("%6.2f ",hVa[j*ROW_SIZE+k]);
            printf("\n");    
        }
        printf("\n");
    	
    	cudaEventRecord(time_start,0);
    	thrust::gather(dmap.begin(),dmap.end(),dVa.begin(),dVb.begin());
    	cudaEventRecord(time_stop,0);
    	cudaEventSynchronize(time_stop);
    	cudaEventElapsedTime(&time_result, time_start, time_stop);
    	hVb=dVb;
        for(long long j=0;j<ROW_SIZE;j++)
        {
            for(long long k=0;k<N;k++) printf("%6.2f ",hVb[j*N+k]);
            printf("\n");    
        }
        printf("\n");
    	printf("Thrust Matrix Size = %lliX%lli\n",ROW_SIZE,N);
    	printf("Thrust Time = %f\n\n", time_result);
    	
    	N<<=1;
        cudaFree(da);
        cudaFree(db);
        free(ha);
        free(hb);
    }
    
    cudaEventDestroy(time_start);
    cudaEventDestroy(time_stop);
}
