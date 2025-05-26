/*
 * БЫСТРАЯ СОРТИРОВКА (QuickSort)
 * 
 * Принцип работы:
 * 1. Выбираем опорный элемент (pivot) - обычно последний элемент
 * 2. Разделяем массив: элементы меньше pivot - слева, больше - справа
 * 3. Рекурсивно сортируем левую и правую части
 * 
 * Сложность: O(n log n) в среднем, O(n²) в худшем случае
 * Худший случай: когда массив уже отсортирован или отсортирован в обратном порядке
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Функция обмена двух элементов местами
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Функция разделения массива на две части относительно опорного элемента
int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // Берем последний элемент как опорный
    int i = (low - 1);        // Индекс меньшего элемента
    
    // Проходим все элементы кроме последнего (опорного)
    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] < pivot) {
            i++;    // Увеличиваем индекс меньшего элемента
            swap(&arr[i], &arr[j]);  // Перемещаем элемент в левую часть
        }
    }
    // Помещаем опорный элемент на правильную позицию
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);  // Возвращаем позицию опорного элемента
}

// Основная рекурсивная функция быстрой сортировки
void quickSort(int arr[], int low, int high) {
    if (low < high) {  // Базовый случай: если есть более одного элемента
        // Разделяем массив и получаем позицию опорного элемента
        int pi = partition(arr, low, high);
        
        // Рекурсивно сортируем левую часть (элементы < pivot)
        quickSort(arr, low, pi - 1);
        // Рекурсивно сортируем правую часть (элементы > pivot)
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Быстрая сортировка ===\n");
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Отсортированный массив: ");
    printArray(arr, n);
    
    return 0;
} 