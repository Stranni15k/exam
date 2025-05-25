#include <iostream>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

const int INITIAL_SIZE = 7;
const double LOAD_FACTOR_THRESHOLD = 0.5;

struct HashEntry {
    int key = -1;
    int value = 0;
    bool isDeleted = false;
};

class HashTableOA {
private:
    std::vector<HashEntry> table;
    int size;
    int count;
    int deletedCount;

    int hash1(int key) const {
        return key % size;
    }

    int hash2(int key) const {
        return 7 - (key % 7);
    }

    int doubleHash(int key, int attempt) const {
        return (hash1(key) + attempt * hash2(key)) % size;
    }

    void rehash() {
        std::cout << "���������������: " << size << " -> " << size * 2 << "\n";
        std::vector<HashEntry> oldTable = table;
        size *= 2;
        table = std::vector<HashEntry>(size);
        count = 0;
        deletedCount = 0;

        for (const auto& entry : oldTable) {
            if (entry.key != -1 && !entry.isDeleted) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTableOA(int initialSize) : size(initialSize), count(0), deletedCount(0) {
        table = std::vector<HashEntry>(size);
    }

    void insert(int key, int value) {
        if ((double)(count + deletedCount) / size > LOAD_FACTOR_THRESHOLD) {
            rehash();
        }

        int attempt = 0;
        int index;

        while (attempt < size) {
            index = doubleHash(key, attempt);

            if (table[index].key == -1 || table[index].isDeleted) {
                if (table[index].isDeleted) deletedCount--;
                table[index] = { key, value, false };
                count++;
                return;
            }

            if (table[index].key == key && !table[index].isDeleted) {
                table[index].value = value;
                return;
            }

            attempt++;
        }

        std::cout << "������: ������� �����������\n";
    }

    bool search(int key, int& value) const {
        int attempt = 0;
        int index;

        while (attempt < size) {
            index = doubleHash(key, attempt);

            if (table[index].key == -1) return false;
            if (table[index].key == key && !table[index].isDeleted) {
                value = table[index].value;
                return true;
            }

            attempt++;
        }

        return false;
    }

    bool remove(int key) {
        int attempt = 0;
        int index;

        while (attempt < size) {
            index = doubleHash(key, attempt);

            if (table[index].key == -1) return false;

            if (table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true;
                count--;
                deletedCount++;
                return true;
            }

            attempt++;
        }

        return false;
    }

    void print() const {
        std::cout << "\n��������� ���-�������:\n";
        std::cout << "������: " << size << ", ���������: " << count
            << ", �������: " << deletedCount
            << ", ����. ��������: " << std::fixed << std::setprecision(2)
            << (double)(count + deletedCount) / size << "\n";

        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "]: ";
            if (table[i].key == -1) {
                std::cout << "�����";
            }
            else if (table[i].isDeleted) {
                std::cout << "������ (" << table[i].key << ":" << table[i].value << ")";
            }
            else {
                std::cout << "(" << table[i].key << ":" << table[i].value << ")";
            }
            std::cout << "\n";
        }
    }

    void printStats() const {
        int empty = 0, active = 0, deleted = 0;
        for (const auto& entry : table) {
            if (entry.key == -1) empty++;
            else if (entry.isDeleted) deleted++;
            else active++;
        }

        std::cout << "\n����������:\n";
        std::cout << "������: " << empty << ", ��������: " << active << ", ���������: " << deleted << "\n";
        std::cout << "����� ��������: " << std::fixed << std::setprecision(2)
            << (double)(active + deleted) / size << "\n";
    }
};

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== ���-������� � �������� ���������� (C++) ===\n";

    HashTableOA table(INITIAL_SIZE);

    int keys[] = { 10, 22, 31, 4, 15, 28, 17, 88, 59 };
    int values[] = { 100, 220, 310, 40, 150, 280, 170, 880, 590 };
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; ++i) {
        std::cout << "������� " << keys[i] << " -> " << values[i] << "\n";
        table.insert(keys[i], values[i]);
        if (i % 3 == 2 || i == n - 1) table.print();
    }

    table.printStats();

    std::cout << "\n����� ������:\n";
    int toSearch[] = { 22, 17, 99, 4, 100 };
    for (int key : toSearch) {
        int value;
        if (table.search(key, value)) {
            std::cout << "���� " << key << " ������, ��������: " << value << "\n";
        }
        else {
            std::cout << "���� " << key << " �� ������\n";
        }
    }

    std::cout << "\n��������:\n";
    int toDelete[] = { 22, 88, 999 };
    for (int key : toDelete) {
        if (table.remove(key)) {
            std::cout << "���� " << key << " ������\n";
        }
        else {
            std::cout << "���� " << key << " �� ������ ��� ��������\n";
        }
    }

    table.print();
    table.printStats();

    return 0;
}
