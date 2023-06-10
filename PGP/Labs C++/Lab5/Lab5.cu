#include<cuda.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

#define SH_DIM 32

float A=-10.0;
float B=20.0;

__global__ void gTranspoteGlobal(float* matr, float* matr_t, long long N, long long K)
{
        int k=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;
        matr_t[n+k*N]=matr[k+n*K];
}

__global__ void gTranspoteSharedDummy(float* matr, float* matr_t, long long N, long long K)
{
	__shared__ float buffer[SH_DIM][SH_DIM];
        int k=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;
		
	buffer[threadIdx.y][threadIdx.x]=matr[k+n*N];
	__syncthreads();

	k=threadIdx.x+blockIdx.y*blockDim.x;
	n=threadIdx.y+blockIdx.x*blockDim.y;
        matr_t[k+n*N]=buffer[threadIdx.x][threadIdx.y];
}

__global__ void gTranspoteSharedNoDummy(float* matr, float* matr_t, long long N, long long K)
{
        __shared__ float buffer[SH_DIM][SH_DIM+1];
        int k=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

        buffer[threadIdx.y][threadIdx.x]=matr[k+n*N];
        __syncthreads();

	k=threadIdx.x+blockIdx.y*blockDim.x;
        n=threadIdx.y+blockIdx.x*blockDim.y;
        matr_t[k+n*N]=buffer[threadIdx.x][threadIdx.y];
}

int main(int argc, char* argv[])
{
        if(argc<2)
        {
                printf("Too low argument in input line!");
                return -1;
        }
        long long N=atoi(argv[1]);
        long long K=atoi(argv[2]);
        long long threads_per_block=32;
        if(N%threads_per_block!=0)
        {
                printf("Wrong Input");
                return 0;
        }
        if(K%threads_per_block!=0)
        {
                printf("Wrong Input");
                return 0;
        }
        float *dmatr,*hmatr,*dmatr_t,*hmatr_t;
        cudaMalloc((void**) &dmatr,N*K*sizeof(float));
        cudaMalloc((void**) &dmatr_t,N*K*sizeof(float));
        hmatr=(float*) calloc(N*K,sizeof(float));
        hmatr_t=(float*) calloc(N*K,sizeof(float));
        for(long long i=0;i<N;i++) for(long long j=0;j<K;j++) hmatr[j+i*K]=j+i*K;//rand()*(B-A)/RAND_MAX+A;
        cudaMemcpy(dmatr,hmatr,K*N*sizeof(float),cudaMemcpyHostToDevice);
        gTranspoteGlobal<<<dim3(K/threads_per_block,N/threads_per_block),dim3(threads_per_block,threads_per_block)>>>(dmatr,dmatr_t,N,K);
        cudaDeviceSynchronize();
        cudaMemcpy(hmatr_t,dmatr_t,K*N*sizeof(float),cudaMemcpyDeviceToHost);
	
	for(long long i=0;i<K;i++)
        {
                for(long long j=0;j<N;j++)
                {
                        printf("%4.0f ",hmatr_t[j+i*N]);
                }
                printf("\n");
        }

	
	cudaFree(dmatr_t);
	free(hmatr_t);
	cudaMalloc((void**) &dmatr_t,N*K*sizeof(float));
	hmatr_t=(float*) calloc(N*K,sizeof(float));
	gTranspoteSharedDummy<<<dim3(K/threads_per_block,N/threads_per_block),dim3(threads_per_block,threads_per_block)>>>(dmatr,dmatr_t,N,K);
        cudaDeviceSynchronize();
	cudaMemcpy(hmatr_t,dmatr_t,K*N*sizeof(float),cudaMemcpyDeviceToHost);
	
	cudaFree(dmatr_t);
        free(hmatr_t);
        cudaMalloc((void**) &dmatr_t,N*K*sizeof(float));
        hmatr_t=(float*) calloc(N*K,sizeof(float));
        gTranspoteSharedNoDummy<<<dim3(K/threads_per_block,N/threads_per_block),dim3(threads_per_block,threads_per_block)>>>(dmatr,dmatr_t,N,K);
        cudaDeviceSynchronize();
        cudaMemcpy(hmatr_t,dmatr_t,K*N*sizeof(float),cudaMemcpyDeviceToHost);

        /*for(long long i=0;i<K;i++)
        {
                for(long long j=0;j<N;j++)
                {
                        printf("%4.0f ",hmatr_t[j+i*N]);
                }
                printf("\n");
        }*/
        cudaFree(dmatr);
        cudaFree(dmatr_t);
        free(hmatr);
        free(hmatr_t);
        return 0;
}

