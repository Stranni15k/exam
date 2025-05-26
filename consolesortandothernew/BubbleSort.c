/*
 * СОРТИРОВКА ПУЗЫРЬКОМ (Bubble Sort)
 *
 * Принцип работы:
 * - Сравниваем соседние элементы
 * - Если они в неправильном порядке - меняем местами
 * - Повторяем пока массив не отсортирован
 * - "Всплывают" максимальные элементы к концу
 *
 * Сложность:
 * - Лучший случай: O(n) - массив уже отсортирован
 * - Средний случай: O(n²)
 * - Худший случай: O(n²) - массив отсортирован в обратном порядке
 * - Память: O(1) - сортировка на месте
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Функция для обмена двух элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Сортировка пузырьком
void bubbleSort(int arr[], int n) {
    printf("Начинаем сортировку пузырьком...\n");
    
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;  // Флаг для оптимизации
        
        printf("Проход %d: ", i + 1);
        
        // Последние i элементов уже отсортированы
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
                printf("(%d↔%d) ", arr[j + 1], arr[j]);
            }
        }
        
        // Выводим состояние массива после каждого прохода
        printf("→ [");
        for (int k = 0; k < n; k++) {
            printf("%d", arr[k]);
            if (k < n - 1) printf(", ");
        }
        printf("]\n");
        
        // Если не было обменов - массив отсортирован
        if (swapped == 0) {
            printf("Массив отсортирован досрочно!\n");
            break;
        }
    }
}

// Вывод массива
void printArray(int arr[], int n, const char* title) {
    printf("%s: [", title);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    printf("=== Сортировка пузырьком ===\n\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printArray(arr, n, "Исходный массив");
    printf("\n");
    
    bubbleSort(arr, n);
    
    printf("\n");
    printArray(arr, n, "Отсортированный массив");
    
    printf("\nСложность: O(n²)\n");
    printf("Стабильная сортировка: Да\n");
    printf("На месте: Да\n");
    
    return 0;
}