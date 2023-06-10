#include <cuda.h>
#include <malloc.h>
#include <stdio.h>

int main()
{
	cudaEvent_t time_start, time_stop;
    cudaEventCreate(&time_start);
    cudaEventCreate(&time_stop);
    float time_result;
    
	long long size=1<<10;
	float *ha, *hb,*da;
	for(int i=0;i<10;i++,size<<=1)
	{
		printf("SizeofVector: %lli\n",size);
		
		ha=(float*)malloc(sizeof(float)*size);
		hb=(float*)malloc(sizeof(float)*size);
		cudaMalloc((void**)&da,sizeof(float)*size);
		memset(ha,21,sizeof(float)*size);
		
		cudaEventRecord(time_start,0);
        cudaMemcpy(da, ha, sizeof(float)*size,cudaMemcpyHostToDevice);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        printf("CopyToDevice: %f\n",time_result);
        
        cudaEventRecord(time_start,0);
        cudaMemcpy(hb, da, sizeof(float)*size,cudaMemcpyDeviceToHost);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        printf("CopyToDevice: %f\n",time_result);
        
        free(ha);
        free(hb);
        cudaFree(da);
        
		cudaMallocHost((void**)&ha,sizeof(float)*size);
		cudaMallocHost((void**)&hb,sizeof(float)*size);
		cudaMalloc((void**)&da,sizeof(float)*size);
		memset(ha,21,sizeof(float)*size);
		
		cudaEventRecord(time_start,0);
        cudaMemcpy(da, ha, sizeof(float)*size,cudaMemcpyHostToDevice);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        printf("CopyToDevice Pinned: %f\n",time_result);
        
        cudaEventRecord(time_start,0);
        cudaMemcpy(hb, da, sizeof(float)*size,cudaMemcpyDeviceToHost);
        cudaEventRecord(time_stop,0);
        cudaEventSynchronize(time_stop);
        cudaEventElapsedTime(&time_result, time_start, time_stop);
        printf("CopyToDevice Pinned: %f\n",time_result);
        
        cudaFreeHost(ha);
        cudaFreeHost(hb);
        cudaFree(da);
        printf("\n");
	}
	
}

