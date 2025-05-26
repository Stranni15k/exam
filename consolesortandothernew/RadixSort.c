/*
 * ПОРАЗРЯДНАЯ СОРТИРОВКА (Radix Sort)
 * 
 * Принцип работы:
 * 1. Сортируем числа по младшему разряду (единицы)
 * 2. Затем по следующему разряду (десятки)
 * 3. Продолжаем до старшего разряда
 * 4. Для сортировки каждого разряда используем Counting Sort
 * 
 * Особенности:
 * - Не сравниваем элементы напрямую
 * - Сложность: O(d × (n + k)), где d - количество разрядов
 * - Для десятичных чисел k = 10
 * - Стабильная сортировка
 * - Эффективна для чисел с небольшим количеством разрядов
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Функция поиска максимального элемента (для определения количества разрядов)
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    free(output);
}

// Основная функция поразрядной сортировки
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);  // Находим максимальное число
    
    // Сортируем по каждому разряду: exp = 1 (единицы), 10 (десятки), 100 (сотни)...
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);  // Применяем counting sort для текущего разряда
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Поразрядная сортировка ===\n");
    int arr[] = {170, 45, 75, 90, 2, 802, 24, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, n);
    
    radixSort(arr, n);
    
    printf("Отсортированный массив: ");
    printArray(arr, n);
    
    return 0;
} 