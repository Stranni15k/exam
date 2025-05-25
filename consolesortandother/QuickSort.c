 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    printf("=== Демонстрация быстрой сортировки ===\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, size);
    
    clock_t start = clock();
    quickSort(arr, 0, size - 1);
    clock_t end = clock();
    
    printf("Отсортированный массив: ");
    printArray(arr, size);
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", time_taken);
    
    return 0;
} 
