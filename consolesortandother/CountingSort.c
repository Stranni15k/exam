 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void countingSort(int arr[], int n) {
    int max = getMax(arr, n);
    
     
    int* count = (int*)calloc(max + 1, sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));
    
     
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
     
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
     
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
     
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(count);
    free(output);
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

    printf("=== Демонстрация сортировки подсчётом ===\n");
    
    int arr[] = {4, 2, 2, 8, 3, 3, 1, 7, 4, 9, 1, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, size);
    
    clock_t start = clock();
    countingSort(arr, size);
    clock_t end = clock();
    
    printf("Отсортированный массив: ");
    printArray(arr, size);
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", time_taken);
    printf("Примечание: работает эффективно для небольших значений элементов\n");
    
    return 0;
} 
