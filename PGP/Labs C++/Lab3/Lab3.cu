#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>

__global__ void gSum(float* a, float* b, float* c)
{
        c[threadIdx.x+blockDim.x*blockIdx.x]=a[threadIdx.x+blockDim.x*blockIdx.x]+b[threadIdx.x+blockDim.x*blockIdx.x];
}

float A=-10.0;
float B=20.0;

int main(int argc, char* argv[])
{
        float *da,*ha,*db,*hb,*dc,*hc;
        long long N=1024;
        long long threads_per_block=1<<atoi(argv[1]);
        long long num_of_blocks;
        for(long long i=0;i<=100;i++)
        {
                num_of_blocks=N/threads_per_block;
                cudaMalloc((void**) &da,N*sizeof(float));
                cudaMalloc((void**) &db,N*sizeof(float));
                cudaMalloc((void**) &dc,N*sizeof(float));
                ha=(float*) calloc(N,sizeof(float));
                for(long long j=0;j<N;j++) ha[j]=rand()*(B-A)/RAND_MAX+A;
                hb=(float*) calloc(N,sizeof(float));
                for(long long j=0;j<N;j++) hb[j]=rand()*(B-A)/RAND_MAX+A;
                hc=(float*) calloc(N,sizeof(float));
                cudaMemcpy(da,ha,N*sizeof(float),cudaMemcpyHostToDevice);
                cudaMemcpy(db,hb,N*sizeof(float),cudaMemcpyHostToDevice);
                cudaDeviceSynchronize();
                gSum<<<dim3(num_of_blocks),dim3(threads_per_block)>>>(da,db,dc);
                cudaDeviceSynchronize();
                cudaMemcpy(hc,dc,N*sizeof(float),cudaMemcpyDeviceToHost);
                //printf("%f %f %f\n",ha[0],hb[0],hc[0]);
                free(ha);
                free(hb);
                free(hc);
                cudaFree(da);
                cudaFree(db);
                cudaFree(dc);
        }
        return 0;
}

