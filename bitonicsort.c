// Copyright of Faisal Almashouq 444105697
#include <stdio.h>
#include <stdlib.h>

void load_data(int** data) {
    printf("Loading data");

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    int i = 0, num;
    int* arr = malloc(100 * sizeof(int*));
    while((fscanf(file, "%d", &num) == 1) && (i < 100)) {
        arr[i++] = num;
    }

    
}

int** bitonic_sort(int** data) {
    printf("Sorting data using Bitonic Merge Sort Algorithm");

    return data;
}
int main() {
    int **unsorted;

    load_data(unsorted);
    if (unsorted == NULL) {
        printf("No data loaded");
        return -1;
    }

    if ((sizeof(unsorted)/sizeof(unsorted[0])) % 2 != 0) {
        printf("Array length must be even");
        return -1;
    }
    

    int** sorted = bitonic_sort(unsorted);
    for (int i = 0; sorted[i] != NULL; i++) {
        printf("The new sorted data: %d ", *sorted[i]);
    }
    
    return 0;
}