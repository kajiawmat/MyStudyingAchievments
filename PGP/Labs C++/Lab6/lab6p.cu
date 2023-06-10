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
__device__ Vertex vert[VERT_SIZE];

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

__device__ int getIndex(int x, int y, int z)
{
    return FGSIZE * (x * FGSIZE + y) + z;
}

__device__ float interpolate(float terms[8], float xd, float yd, float zd)
{
	float termsG1[4];
	float termsG2[2];
    termsG1[0b00] = terms[0b000] * (1 - xd) + terms[0b100] * xd;
    termsG1[0b01] = terms[0b001] * (1 - xd) + terms[0b101] * xd;

    termsG1[0b10] = terms[0b010] * (1 - xd) + terms[0b110] * xd;
    termsG1[0b11] = terms[0b011] * (1 - xd) + terms[0b111] * xd;

    termsG2[0b0] = termsG1[0b00] * (1 - yd) + termsG1[0b10] * yd;
    termsG2[0b1] = termsG1[0b01] * (1 - yd) + termsG1[0b11] * yd;

    return termsG2[0b0] * (1 - zd) + termsG2[0b1] * zd;
}

__global__ void kernelp(float *arr, float *sum)
{
    __shared__ float cache[THREADS_PER_BLOCK];
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int cacheIndex = threadIdx.x;
    float xf = vert[tid].x+ FGSHIFT;
    float yf = vert[tid].y+ FGSHIFT;
    float zf = vert[tid].z+ FGSHIFT;

    float p;
    int x;
    int y;
    int z;
    xf = modf(xf, &p);
    x = p;
    yf = modf(yf, &p);
    y = p;
    zf = modf(zf, &p);
    z = p;

	float terms[8];
    terms[0b000] = arr[getIndex(x, y, z)];
    terms[0b001] = arr[getIndex(x, y, z + 1)];
    terms[0b010] = arr[getIndex(x, y + 1, z)];
    terms[0b011] = arr[getIndex(x, y + 1, z + 1)];
    terms[0b100] = arr[getIndex(x + 1, y, z)];
    terms[0b101] = arr[getIndex(x + 1, y, z + 1)];
    terms[0b110] = arr[getIndex(x + 1, y + 1, z)];
    terms[0b111] = arr[getIndex(x + 1, y + 1, z + 1)];

    cache[cacheIndex] = interpolate(terms, xf, yf, zf);
    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (cacheIndex < s)
            cache[cacheIndex] += cache[cacheIndex + s];
        __syncthreads();
    }
    if (cacheIndex == 0)	sum[blockIdx.x] = cache[0];
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
    cudaMemcpy(arr_dev, arr, sizeof(float) * FGSIZE * FGSIZE * FGSIZE, cudaMemcpyHostToDevice);


    kernelp<<<BLOCKS_PER_GRID, THREADS_PER_BLOCK>>>(arr_dev, sum_dev);

    cudaDeviceSynchronize();
    cudaMemcpy(sum, sum_dev, sizeof(float) * BLOCKS_PER_GRID, cudaMemcpyDeviceToHost);
    for (int i = 0; i < BLOCKS_PER_GRID; ++i)
        sumsSum += sum[i];
    printf("Sump = %f\n", sumsSum * M_PI * M_PI / COEF / COEF);
    
    cudaFree(sum_dev);
    free(sum);
    cudaFree(arr_dev);
    free(arr);

    return 0;
}
