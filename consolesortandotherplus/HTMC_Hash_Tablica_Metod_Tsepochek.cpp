#include <iostream>
#include <vector>
#include <list>

#ifdef _WIN32
#include <windows.h>
#endif

const int INITIAL_SIZE = 7;
const double LOAD_FACTOR_THRESHOLD = 0.75;

struct HashNode {
    int key;
    int value;
    HashNode(int k, int v) : key(k), value(v) {}
};

class HashTable {
private:
    std::vector<std::list<HashNode>> table;
    int size;
    int count;

    int hash1(int key) const {
        return key % size;
    }

    void rehash() {
        std::cout << "Перехеширование: увеличиваем размер с " << size << " до " << size * 2 << "\n";
        std::vector<std::list<HashNode>> oldTable = table;

        size *= 2;
        count = 0;
        table.clear();
        table.resize(size);

        for (const auto& bucket : oldTable) {
            for (const auto& node : bucket) {
                insert(node.key, node.value);
            }
        }
        std::cout << "Перехеширование завершено. Новый размер: " << size << "\n";
    }

public:
    HashTable(int initSize = INITIAL_SIZE) : size(initSize), count(0) {
        table.resize(size);
    }

    void insert(int key, int value) {
        if ((double)count / size > LOAD_FACTOR_THRESHOLD) {
            rehash();
        }

        int index = hash1(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        count++;
    }

    bool search(int key, int& value) const {
        int index = hash1(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = hash1(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                count--;
                return true;
            }
        }
        return false;
    }

    void print() const {
        std::cout << "\nСостояние хеш-таблицы (метод цепочек):\n";
        std::cout << "Размер: " << size << ", Элементов: " << count
            << ", Коэффициент загрузки: " << (double)count / size << "\n";

        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "]: ";
            if (table[i].empty()) {
                std::cout << "пусто";
            }
            else {
                for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                    std::cout << "(" << it->key << ":" << it->value << ")";
                    if (std::next(it) != table[i].end()) std::cout << " -> ";
                }
            }
            std::cout << "\n";
        }
    }

    void printStatistics() const {
        int empty = 0;
        int maxLen = 0;
        int totalLen = 0;

        for (const auto& bucket : table) {
            int len = bucket.size();
            if (len == 0) empty++;
            else {
                totalLen += len;
                if (len > maxLen) maxLen = len;
            }
        }

        std::cout << "\nСтатистика:\n";
        std::cout << "Пустых ячеек: " << empty << "\n";
        std::cout << "Максимальная длина цепочки: " << maxLen << "\n";
        std::cout << "Средняя длина цепочки: "
            << (count > 0 ? (double)totalLen / (size - empty) : 0.0) << "\n";
    }
};

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация хеш-таблицы с методом цепочек ===\n";

    HashTable table;

    int keys[] = { 10, 22, 31, 4, 15, 28, 17, 88, 59, 6, 13, 20, 27 };
    int values[] = { 100, 220, 310, 40, 150, 280, 170, 880, 590, 60, 130, 200, 270 };
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; ++i) {
        std::cout << "Вставляем ключ " << keys[i] << " со значением " << values[i] << "\n";
        table.insert(keys[i], values[i]);
        if (i % 5 == 4 || i == n - 1) {
            table.print();
        }
    }

    table.printStatistics();

    std::cout << "\nПоиск элементов:\n";
    int searchKeys[] = { 22, 17, 99, 6, 100 };
    for (int key : searchKeys) {
        int value;
        if (table.search(key, value)) {
            std::cout << "Ключ " << key << " найден, значение: " << value << "\n";
        }
        else {
            std::cout << "Ключ " << key << " не найден\n";
        }
    }

    std::cout << "\nУдаление элементов:\n";
    int deleteKeys[] = { 22, 88, 999 };
    for (int key : deleteKeys) {
        if (table.remove(key)) {
            std::cout << "Ключ " << key << " успешно удален\n";
        }
        else {
            std::cout << "Ключ " << key << " не найден для удаления\n";
        }
    }

    table.print();
    table.printStatistics();

    return 0;
}
