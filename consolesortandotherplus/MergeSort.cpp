#include <iostream>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        arr[k++] = (leftArr[i] <= rightArr[j]) ? leftArr[i++] : rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr)
        std::cout << num << " ";
    std::cout << "\n";
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация сортировки слиянием (C++) ===\n";

    std::vector<int> arr = { 38, 27, 43, 3, 9, 82, 10, 1, 76, 15 };

    std::cout << "Исходный массив: ";
    printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Отсортированный массив: ";
    printArray(arr);

    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения: " << duration.count() << " секунд\n";

    return 0;
}
