#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/inner_product.h>

using namespace std;

#define MAX 8.0
#define MIN -8.0
#define THREADS_PER_BLOCK 32
#define NUM_OF_BLOCKS 32

struct range_functor
{
	int max;
	range_functor(int _max):max(_max) {}
	__host__ __device__ float operator()(float x) {
		return (float)((long long)x%max);
	}
};

__global__ void gInit(float* a)
{
	a[threadIdx.x+blockDim.x*blockIdx.x]=0.0f;
}

__global__ void gScalar(float *da, float *db, float *dsum)
{
	long long i=threadIdx.x+blockDim.x*blockIdx.x;
	__shared__ float cache[THREADS_PER_BLOCK];
	int thread=threadIdx.x;
	cache[thread]=da[i]*db[i];
	__syncthreads();
	for (int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (thread < s) cache[thread] += cache[thread+s];
        __syncthreads();
    }
    if(thread==0) dsum[blockIdx.x]+=cache[0];
}

int main()
{
	cudaEvent_t time_start, time_stop;
	cudaEventCreate(&time_start);
    cudaEventCreate(&time_stop);
    float time_result;
    
    float *ha,*hb,*da,*db,*hsum,*dsum;
    float sum;

    long long N=32;

    range_functor R(32);
    thrust::device_vector<float> dVa;
    thrust::device_vector<float> dVb;
    for(long long i=0;i<5;i++)
    {
	sum=0;
	hsum=(float*) malloc(sizeof(float)*NUM_OF_BLOCKS);
    	ha=(float*) malloc(N*sizeof(float));
    	hb=(float*) malloc(N*sizeof(float));
    	cudaMalloc((void**) &da,N*sizeof(float));
        cudaMalloc((void**) &db,N*sizeof(float));
	cudaMalloc((void**) &dsum,sizeof(float)*NUM_OF_BLOCKS);
	gInit<<<NUM_OF_BLOCKS, THREADS_PER_BLOCK>>>(dsum);
    	for(long long j=0;j<N;j++)
    	{
    		//ha[j]=rand()*(MAX-MIN)/RAND_MAX+MIN;
    		//hb[j]=rand()*(MAX-MIN)/RAND_MAX+MIN;
		ha[j]=(float)(j%32);
		hb[j]=(float)(j%32);
    		printf("%6.2f ",ha[j]);
    	}
    	printf("\n");
    	for(long long j=0;j<N;j++) printf("%6.2f ",ha[j]);
    	cudaMemcpy(da,ha,N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(db,hb,N*sizeof(float),cudaMemcpyHostToDevice);
    	cudaEventRecord(time_start,0);
    	gScalar<<<NUM_OF_BLOCKS, THREADS_PER_BLOCK>>>(da,db,dsum);
	cudaDeviceSynchronize();
	cudaMemcpy(hsum,dsum,sizeof(float)*NUM_OF_BLOCKS,cudaMemcpyDeviceToHost);
	for(int j=0;j<NUM_OF_BLOCKS;j++) sum+=hsum[j];
        cudaEventRecord(time_stop,0);
    	cudaEventSynchronize(time_stop);
    	cudaEventElapsedTime(&time_result, time_start, time_stop);
    	cudaDeviceSynchronize();
	printf("Vector Size = %lli\n",N);
    	printf("Scalar = %f\n", sum);
    	printf("Time = %f\n", time_result);


	dVa=thrust::device_vector<float>(N);
    	dVb=thrust::device_vector<float>(N);
    	
    	thrust::sequence(thrust::device,dVa.begin(),dVa.end());
    	thrust::sequence(thrust::device,dVb.begin(),dVb.end());
    	thrust::transform(dVa.begin(),dVa.end(),dVa.begin(),R);
    	thrust::transform(dVb.begin(),dVb.end(),dVb.begin(),R);
    	
    	cudaEventRecord(time_start,0);
    	sum=thrust::inner_product(dVa.begin(),dVa.end(),dVb.begin(),0.0f);
    	cudaEventRecord(time_stop,0);
    	cudaEventSynchronize(time_stop);
    	cudaEventElapsedTime(&time_result, time_start, time_stop);
    	cudaDeviceSynchronize();
    	printf("Thrust Vector Size = %lli\n",N);
    	printf("Thrust Scalar = %f\n", sum);
    	printf("Thrust Time = %f\n", time_result);

    	N<<=1;
	cudaFree(da);
	cudaFree(db);
	cudaFree(dsum);
	free(ha);
	free(hb);
	free(hsum);
    }
    
    cudaEventDestroy(time_start);
    cudaEventDestroy(time_stop);
}
