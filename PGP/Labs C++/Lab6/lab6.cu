#include <cuda.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define COEF 24
#define VERT_SIZE 2 * COEF *COEF
#define RADIUS 120.0f
#define FGSIZE 240
#define FGSHIFT FGSIZE / 2
#define MIN(A, B) (A < B ? A : B)
#define THREADS_PER_BLOCK 32
#define BLOCKS_PER_GRID MIN(32, (VERT_SIZE + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK)

struct Vertex
{
    float x, y, z;
};

cudaArray *df_Array = 0;
texture<float, 3, cudaReadModeElementType> df_tex;
__constant__ Vertex vert[VERT_SIZE];

float func(float x, float y, float z)
{
    return y * y * z * z * sqrt(1 - z * z / RADIUS / RADIUS) * sqrt(1 - y * y / RADIUS / RADIUS) / RADIUS / RADIUS /
           RADIUS;
}

void calc_f(float *arr_f)
{
    for (int x = 0; x < FGSIZE; ++x)
        for (int y = 0; y < FGSIZE; ++y)
            for (int z = 0; z < FGSIZE; ++z)
                arr_f[FGSIZE * (x * FGSIZE + y) + z] = func(x - FGSHIFT, y - FGSHIFT, z - FGSHIFT);
}

void init_vertices()
{
    Vertex *temp_vert = (Vertex *)malloc(sizeof(Vertex) * VERT_SIZE);
    int i = 0;
    for (int iphi = 0; iphi < 2 * COEF; ++iphi)
        for (int ipsi = 0; ipsi < COEF; ++ipsi, ++i)
        {
            float phi = iphi * M_PI / COEF;
            float psi = ipsi * M_PI / COEF;
            temp_vert[i].x = RADIUS * sinf(psi) * cosf(phi);
            temp_vert[i].y = RADIUS * sinf(psi) * sinf(phi);
            temp_vert[i].z = RADIUS * cosf(psi);
        }
    cudaMemcpyToSymbol(vert, temp_vert, sizeof(Vertex) * VERT_SIZE, 0, cudaMemcpyHostToDevice);
    free(temp_vert);
}

void load_texture(float *df_h)
{
    const cudaExtent volumeSize = make_cudaExtent(FGSIZE, FGSIZE, FGSIZE);
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
    cudaMalloc3DArray(&df_Array, &channelDesc, volumeSize);
    cudaMemcpy3DParms cpyParams = {0};
    cpyParams.srcPtr =
        make_cudaPitchedPtr((void *)df_h, volumeSize.width * sizeof(float), volumeSize.width, volumeSize.height);
    cpyParams.dstArray = df_Array;
    cpyParams.extent = volumeSize;
    cpyParams.kind = cudaMemcpyHostToDevice;
    cudaMemcpy3D(&cpyParams);
    df_tex.normalized = false;
    df_tex.filterMode = cudaFilterModeLinear;
    df_tex.addressMode[0] = cudaAddressModeClamp;
    df_tex.addressMode[1] = cudaAddressModeClamp;
    df_tex.addressMode[2] = cudaAddressModeClamp;
    cudaBindTextureToArray(df_tex, df_Array, channelDesc);
}

__global__ void kernel(float *a)
{
    __shared__ float cache[THREADS_PER_BLOCK];
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int cacheIndex = threadIdx.x;
    float x = vert[tid].x + FGSHIFT;
    float y = vert[tid].y + FGSHIFT;
    float z = vert[tid].z + FGSHIFT;
    cache[cacheIndex] = tex3D(df_tex, z,y,x);
    __syncthreads();
    for (int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (cacheIndex < s)
            cache[cacheIndex] += cache[cacheIndex + s];
        __syncthreads();
    }
    if (cacheIndex == 0) a[blockIdx.x] = cache[0];
}

void release_texture()
{
    cudaUnbindTexture(df_tex);
    cudaFreeArray(df_Array);
}


int main(int argc, char *argv[])
{
    float *arr = (float *)malloc(sizeof(float) * FGSIZE * FGSIZE * FGSIZE);
    float *arr_dev;
    float *sum = (float *)malloc(sizeof(float) * BLOCKS_PER_GRID);
    float *sum_dev;
    float sumsSum = 0.0f;
    cudaMalloc((void **)&sum_dev, sizeof(float) * BLOCKS_PER_GRID);
    cudaMalloc((void **)&arr_dev, sizeof(float) * FGSIZE * FGSIZE * FGSIZE);

	calc_f(arr);
    init_vertices();
    load_texture(arr);
    
    kernel<<<BLOCKS_PER_GRID, THREADS_PER_BLOCK>>>(sum_dev);

    cudaDeviceSynchronize();
    cudaMemcpy(sum, sum_dev, sizeof(float) * BLOCKS_PER_GRID, cudaMemcpyDeviceToHost);
    for (int i = 0; i < BLOCKS_PER_GRID; ++i)
        sumsSum += sum[i];
    printf("Sum = %f\n", sumsSum * M_PI * M_PI / COEF / COEF);

    cudaFree(sum_dev);
    free(sum);
    release_texture();
    cudaFree(arr_dev);
    free(arr);
    return 0;
}
