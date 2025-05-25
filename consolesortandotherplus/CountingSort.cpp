#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

int getMax(const std::vector<int>& arr) {
    int max = arr[0];
    for (int val : arr) {
        if (val > max) max = val;
    }
    return max;
}

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max = getMax(arr);

    std::vector<int> count(max + 1, 0);
    std::vector<int> output(arr.size());

    for (int val : arr) {
        count[val]++;
    }

    for (int i = 1; i <= max; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    arr = output;
}

void printArray(const std::vector<int>& arr) {
    for (int val : arr)
        std::cout << val << " ";
    std::cout << "\n";
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация сортировки подсчётом ===\n";

    std::vector<int> arr = { 4, 2, 2, 8, 3, 3, 1, 7, 4, 9, 1, 2 };

    std::cout << "Исходный массив: ";
    printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();
    countingSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Отсортированный массив: ";
    printArray(arr);

    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд\n";
    std::cout << "Примечание: эффективно для небольшого диапазона значений\n";

    return 0;
}
