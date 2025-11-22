// Copyright of Faisal Almashouq 444105697 - Parallel VIA CUDA
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#define N 1024

__global__ void bitonic_sort_device(int *data, int size) {
    // To do
}

int load_data(int *unsorted) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int i = 0, num;
    printf("Unsored Array:\n");

    while((fscanf(file, "%d", &num) == 1) && (i < 100)) {
        unsorted[i++] = num;
        printf("%d ", num);
    }

    fclose(file);
    return i;
}

void bitonic_sort_host(int* unsorted, int* d_data, int* sorted, int size) {

    cudaMemcpy(d_data, unsorted, size * sizeof(int), cudaMemcpyHostToDevice);
    
    int blocks = (size + 255) / 256;
    int threads = 256;

    bitonic_sort_device<<<blocks, threads>>>(d_data, size);

    cudaDeviceSynchronize();

    cudaMemcpy(sorted, d_data, size * sizeof(int), cudaMemcpyDeviceToHost);
}



int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    int *unsorted = (int*)malloc(100 * sizeof(int)), *sorted = (int*)malloc(100 * sizeof(int));
    int *d_data;

    int size = load_data(unsorted);

    if (is_power_of_two(size) == 0) {
        printf("Array size must be a power of 2.\n");
        free(unsorted);
        return -1;
    }

    cudaMalloc((void**)&d_data, size * sizeof(int));

    bitonic_sort_host(unsorted, d_data, sorted, size);

    cudaFree(d_data);

    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", sorted[i]);
    }

    free(unsorted);
    free(sorted);
}