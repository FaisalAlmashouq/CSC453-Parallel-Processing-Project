// Understanding cuda parallel programming model - Faisal Almashouq 444105697
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#define N 1024

__global__ void kernel_add(int *a, int *b, int *c) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < N) {
        c[index] = a[index] + b[index];
    }
}

int main () {
    int *a, *b, *c, *d_a, *d_b, *d_c;
    int size = N * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }



    cudaMalloc((int*)d_a, size);
    cudaMalloc((int*)d_b, size);
    cudaMalloc((int*)d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    kernel_add<<<(N + 255) / 256, 256>>>(d_a, d_b, d_c);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    for (int i = 0; i < 10; i++) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

    return 0;
}