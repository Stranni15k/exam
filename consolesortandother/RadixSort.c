 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
     
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
     
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
     
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
     
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    
     
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
        
        printf("После сортировки по разряду %d: ", exp);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация поразрядной сортировки ===\n");
    
    int arr[] = {170, 45, 75, 90, 2, 802, 24, 66, 121, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, size);
    printf("\nПроцесс сортировки:\n");
    
    clock_t start = clock();
    radixSort(arr, size);
    clock_t end = clock();
    
    printf("\nИтоговый отсортированный массив: ");
    printArray(arr, size);
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", time_taken);
    
    return 0;
} 
