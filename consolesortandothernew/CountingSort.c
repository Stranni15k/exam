/*
 * СОРТИРОВКА ПОДСЧЁТОМ (Counting Sort)
 * 
 * Принцип работы:
 * 1. Находим максимальное значение в массиве
 * 2. Создаем массив count для подсчета частоты каждого элемента
 * 3. Подсчитываем количество вхождений каждого элемента
 * 4. Преобразуем count в массив позиций
 * 5. Восстанавливаем отсортированный массив
 * 
 * Особенности:
 * - Не использует сравнения элементов
 * - Линейная сложность O(n + k), где k - диапазон значений
 * - Стабильная сортировка
 * - Требует дополнительной памяти O(k)
 * - Эффективна когда k = O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Основная функция сортировки подсчётом
void countingSort(int arr[], int n) {
    // Шаг 1: Находим максимальный элемент
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    
    // Шаг 2: Создаем массивы для подсчета и вывода
    int* count = (int*)calloc(max + 1, sizeof(int));  // Массив частот (обнулен)
    int* output = (int*)malloc(n * sizeof(int));       // Выходной массив
    
    // Шаг 3: Подсчитываем частоту каждого элемента
    for (int i = 0; i < n; i++)
        count[arr[i]]++;  // count[x] = количество элементов равных x
    
    // Шаг 4: Преобразуем count в массив позиций
    // count[i] теперь содержит количество элементов <= i
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
    
    // Шаг 5: Строим выходной массив (справа налево для стабильности)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];  // Помещаем элемент на правильную позицию
        count[arr[i]]--;                     // Уменьшаем счетчик для следующих таких же элементов
    }
    
    // Шаг 6: Копируем результат обратно в исходный массив
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    // Освобождаем память
    free(count);
    free(output);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Сортировка подсчётом ===\n");
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив: ");
    printArray(arr, n);
    
    countingSort(arr, n);
    
    printf("Отсортированный массив: ");
    printArray(arr, n);
    
    return 0;
} 