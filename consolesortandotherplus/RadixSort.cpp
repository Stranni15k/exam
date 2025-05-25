#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

int getMax(const std::vector<int>& arr) {
    int max = arr[0];
    for (int val : arr) {
        if (val > max)
            max = val;
    }
    return max;
}

void countSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(std::vector<int>& arr) {
    int max = getMax(arr);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, exp);

        std::cout << "После сортировки по разряду " << exp << ": ";
        for (int num : arr)
            std::cout << num << " ";
        std::cout << "\n";
    }
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

    std::cout << "=== Демонстрация поразрядной сортировки (C++) ===\n";

    std::vector<int> arr = { 170, 45, 75, 90, 2, 802, 24, 66, 121, 3 };

    std::cout << "Исходный массив: ";
    printArray(arr);
    std::cout << "\nПроцесс сортировки:\n";

    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "\nИтоговый отсортированный массив: ";
    printArray(arr);

    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд\n";

    return 0;
}
