#include<cuda.h>
#include<stdlib.h>
#include<stdio.h>

#define COUNT_STREAM 4
#define SIZE_VECTOR (1<<15)
#define THREADS_PER_BLOCK 1
#define STEP SIZE_VECTOR/COUNT_STREAM

__global__ void gInit(float *da)
{
	long long i=threadIdx.x + blockIdx.x*blockDim.x;
	da[i]=(float)i;
}

__global__ void gSum(float *da, float *db, float *dc)
{
	long long i=threadIdx.x + blockIdx.x*blockDim.x;
	dc[i]=da[i]+db[i];
}

void printVector(float *da, long long N)
{
	for(long long i=0;i<N;i++) printf("%6.0f ",da[i]);
	printf("\n");
}

int main()
{
	cudaEvent_t time_start, time_stop;
    cudaEventCreate(&time_start);
    cudaEventCreate(&time_stop);
    cudaStream_t *streams;
    float time_result;
    
    float *ha,*hb,*hc,*da,*db,*dc;
    long long portion=THREADS_PER_BLOCK;
    
    cudaMallocHost((void**)&ha,SIZE_VECTOR*sizeof(float));
    cudaMallocHost((void**)&hb,SIZE_VECTOR*sizeof(float));
    cudaMallocHost((void**)&hc,SIZE_VECTOR*sizeof(float));
    
    streams = (cudaStream_t*)calloc(COUNT_STREAM,sizeof(cudaStream_t));
    for(int i = 0; i < COUNT_STREAM; i++){
        cudaStreamCreate(&streams[i]);
    }
    
    for(int i=0;i<=10;i++)
    {
    	cudaMalloc((void**)&da,SIZE_VECTOR*sizeof(float));
    	cudaMalloc((void**)&db,SIZE_VECTOR*sizeof(float));
    	cudaMalloc((void**)&dc,SIZE_VECTOR*sizeof(float));
    	gInit<<<dim3(SIZE_VECTOR/portion),dim3(portion)>>>(da);
    	gInit<<<dim3(SIZE_VECTOR/portion),dim3(portion)>>>(db);
    	cudaEventRecord(time_start,0);
    	for(int i=0;i<COUNT_STREAM;i++)
    	{
    		gSum<<<dim3(SIZE_VECTOR/portion),dim3(portion),0,streams[i]>>>(da,db,dc);
    	}
    	for(int i=0;i<COUNT_STREAM;i++)
		{
        	cudaStreamSynchronize(streams[i]);
    	}
    	cudaEventRecord(time_stop,0);
    	cudaEventSynchronize(time_stop);
    	cudaEventElapsedTime(&time_result, time_start, time_stop);
    	for(int i=0;i<COUNT_STREAM;i++)
    	{
    		cudaMemcpyAsync(ha+(i*STEP),da+(i*STEP),sizeof(float)*STEP,cudaMemcpyDeviceToHost,streams[i]);
    		cudaMemcpyAsync(hb+(i*STEP),db+(i*STEP),sizeof(float)*STEP,cudaMemcpyDeviceToHost,streams[i]);
    		cudaMemcpyAsync(hc+(i*STEP),dc+(i*STEP),sizeof(float)*STEP,cudaMemcpyDeviceToHost,streams[i]);
    	}
    	for(int i=0;i<COUNT_STREAM;i++)
		{
                cudaStreamSynchronize(streams[i]);
        }
	//printVector(ha,SIZE_VECTOR);
    	//printVector(hb,SIZE_VECTOR);
    	//printVector(hc,SIZE_VECTOR);
    	printf("Portion: %lli\n",portion);
    	printf("gSum: %f\n",time_result);
    	portion<<=1;
    	cudaFree(da);
    	cudaFree(db);
    	cudaFree(dc);
    }
    cudaFreeHost(ha);
    cudaFreeHost(hb);
    cudaFreeHost(hc);
    cudaEventDestroy(time_start);
    cudaEventDestroy(time_stop);
}
