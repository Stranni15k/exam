#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // опорный элемент
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr)
        std::cout << num << " ";
    std::cout << '\n';
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация быстрой сортировки (C++) ===\n";

    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42 };

    std::cout << "Исходный массив: ";
    printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Отсортированный массив: ";
    printArray(arr);

    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд\n";

    return 0;
}
