#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void printArray(const std::vector<int>& arr) {
    for (int value : arr)
        std::cout << value << " ";
    std::cout << "\n";
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация сортировки пузырьком ===\n";

    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 30 };

    std::cout << "Исходный массив: ";
    printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Отсортированный массив: ";
    printArray(arr);

    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд\n";

    return 0;
}
