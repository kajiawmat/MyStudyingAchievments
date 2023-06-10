#include<cuda.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

float A=-10.0;
float B=20.0;

__global__ void gTranspoteGlobal(float* matr, float* matr_t, long long N, long long K)
{
	int k=threadIdx.x+blockIdx.x*blockDim.x;
	int n=threadIdx.y+blockIdx.y*blockDim.y;
	
	matr_t[n+k*N]=matr[k+n*K];
}

__global__ void gInit(float* matr, long long K)
{
	int k=threadIdx.x+blockIdx.x*blockDim.x;
        int n=threadIdx.y+blockIdx.y*blockDim.y;

	matr[k+n*K]=k+n*K;
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
	gInit<<<dim3(K/threads_per_block,N/threads_per_block),dim3(threads_per_block,threads_per_block)>>>(dmatr,K);
	cudaDeviceSynchronize();
	cudaMemcpy(hmatr,dmatr,K*N*sizeof(float),cudaMemcpyDeviceToHost);
	gTranspoteGlobal<<<dim3(K/threads_per_block,N/threads_per_block),dim3(threads_per_block,threads_per_block)>>>(dmatr,dmatr_t,N,K);
	cudaDeviceSynchronize();
	cudaMemcpy(hmatr_t,dmatr_t,K*N*sizeof(float),cudaMemcpyDeviceToHost);
	for(long long i=0;i<N;i++)
        {
                for(long long j=0;j<K;j++)
                {
                        printf("%4.0f ",hmatr[j+i*K]);
                }
                printf("\n");
        }
	for(long long i=0;i<K;i++) 
	{
		for(long long j=0;j<N;j++)
		{
			printf("%4.0f ",hmatr_t[j+i*N]);
		}
		printf("\n");
	}
	cudaFree(dmatr);
	cudaFree(dmatr_t);
	free(hmatr);
	free(hmatr_t);
	return 0;
}
