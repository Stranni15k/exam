 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define INITIAL_SIZE 7
#define LOAD_FACTOR_THRESHOLD 0.5
#define DELETED -2147483648   

struct HashEntry {
    int key;
    int value;
    int isDeleted;   
};

struct HashTableOA {
    struct HashEntry* table;
    int size;
    int count;
    int deletedCount;
};

typedef struct HashEntry HashEntry;
typedef struct HashTableOA HashTableOA;

 
HashTableOA* createHashTableOA(int size) {
    HashTableOA* hashTable = (HashTableOA*)malloc(sizeof(HashTableOA));
    hashTable->size = size;
    hashTable->count = 0;
    hashTable->deletedCount = 0;
    hashTable->table = (HashEntry*)malloc(size * sizeof(HashEntry));
    
     
    for (int i = 0; i < size; i++) {
        hashTable->table[i].key = -1;   
        hashTable->table[i].value = 0;
        hashTable->table[i].isDeleted = 0;
    }
    
    return hashTable;
}

 
int hash1(int key, int size) {
    return key % size;
}

 
int hash2(int key, int size) {
    return 7 - (key % 7);
}

 
int doubleHash(int key, int size, int attempt) {
    return (hash1(key, size) + attempt * hash2(key, size)) % size;
}

 
void insertOA(HashTableOA* hashTable, int key, int value);

 
void rehashOA(HashTableOA* hashTable) {
    printf("Перехеширование: увеличиваем размер с %d до %d\n", hashTable->size, hashTable->size * 2);
    
    HashEntry* oldTable = hashTable->table;
    int oldSize = hashTable->size;
    
     
    hashTable->size = oldSize * 2;
    hashTable->count = 0;
    hashTable->deletedCount = 0;
    hashTable->table = (HashEntry*)malloc(hashTable->size * sizeof(HashEntry));
    
     
    for (int i = 0; i < hashTable->size; i++) {
        hashTable->table[i].key = -1;
        hashTable->table[i].value = 0;
        hashTable->table[i].isDeleted = 0;
    }
    
     
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && !oldTable[i].isDeleted) {
            insertOA(hashTable, oldTable[i].key, oldTable[i].value);
        }
    }
    
    free(oldTable);
    printf("Перехеширование завершено. Новый размер: %d\n", hashTable->size);
}

 
void insertOA(HashTableOA* hashTable, int key, int value) {
     
    double loadFactor = (double)(hashTable->count + hashTable->deletedCount) / hashTable->size;
    if (loadFactor > LOAD_FACTOR_THRESHOLD) {
        rehashOA(hashTable);
    }
    
    int attempt = 0;
    int index;
    
    do {
        index = doubleHash(key, hashTable->size, attempt);
        
         
        if (hashTable->table[index].key == -1 || hashTable->table[index].isDeleted) {
            if (hashTable->table[index].isDeleted) {
                hashTable->deletedCount--;
            }
            hashTable->table[index].key = key;
            hashTable->table[index].value = value;
            hashTable->table[index].isDeleted = 0;
            hashTable->count++;
            return;
        }
        
         
        if (hashTable->table[index].key == key && !hashTable->table[index].isDeleted) {
            hashTable->table[index].value = value;
            return;
        }
        
        attempt++;
    } while (attempt < hashTable->size);
    
    printf("Ошибка: не удалось вставить элемент (таблица переполнена)\n");
}

 
int searchOA(HashTableOA* hashTable, int key, int* found) {
    int attempt = 0;
    int index;
    
    do {
        index = doubleHash(key, hashTable->size, attempt);
        
         
        if (hashTable->table[index].key == -1) {
            *found = 0;
            return -1;
        }
        
         
        if (hashTable->table[index].key == key && !hashTable->table[index].isDeleted) {
            *found = 1;
            return hashTable->table[index].value;
        }
        
        attempt++;
    } while (attempt < hashTable->size);
    
    *found = 0;
    return -1;
}

 
int deleteKeyOA(HashTableOA* hashTable, int key) {
    int attempt = 0;
    int index;
    
    do {
        index = doubleHash(key, hashTable->size, attempt);
        
         
        if (hashTable->table[index].key == -1) {
            return 0;
        }
        
         
        if (hashTable->table[index].key == key && !hashTable->table[index].isDeleted) {
            hashTable->table[index].isDeleted = 1;
            hashTable->count--;
            hashTable->deletedCount++;
            return 1;
        }
        
        attempt++;
    } while (attempt < hashTable->size);
    
    return 0;
}

 
void printHashTableOA(HashTableOA* hashTable) {
    printf("\nСостояние хеш-таблицы (открытая адресация):\n");
    printf("Размер: %d, Элементов: %d, Удаленных: %d, Коэффициент загрузки: %.2f\n", 
           hashTable->size, hashTable->count, hashTable->deletedCount,
           (double)(hashTable->count + hashTable->deletedCount) / hashTable->size);
    
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d]: ", i);
        if (hashTable->table[i].key == -1) {
            printf("пусто");
        } else if (hashTable->table[i].isDeleted) {
            printf("удален(%d:%d)", hashTable->table[i].key, hashTable->table[i].value);
        } else {
            printf("(%d:%d)", hashTable->table[i].key, hashTable->table[i].value);
        }
        printf("\n");
    }
}

 
void demonstrateSearch(HashTableOA* hashTable, int key) {
    printf("\nДемонстрация поиска ключа %d:\n", key);
    int attempt = 0;
    int index;
    
    do {
        index = doubleHash(key, hashTable->size, attempt);
        printf("Попытка %d: индекс %d", attempt, index);
        
        if (hashTable->table[index].key == -1) {
            printf(" - пусто, поиск завершен (не найден)\n");
            break;
        } else if (hashTable->table[index].key == key && !hashTable->table[index].isDeleted) {
            printf(" - найден! Значение: %d\n", hashTable->table[index].value);
            break;
        } else if (hashTable->table[index].isDeleted) {
            printf(" - удаленный элемент (%d), продолжаем поиск\n", hashTable->table[index].key);
        } else {
            printf(" - другой ключ (%d), продолжаем поиск\n", hashTable->table[index].key);
        }
        
        attempt++;
    } while (attempt < hashTable->size);
}

 
void printStatisticsOA(HashTableOA* hashTable) {
    int emptySlots = 0;
    int activeSlots = 0;
    int deletedSlots = 0;
    
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].key == -1) {
            emptySlots++;
        } else if (hashTable->table[i].isDeleted) {
            deletedSlots++;
        } else {
            activeSlots++;
        }
    }
    
    printf("\nСтатистика:\n");
    printf("Пустых ячеек: %d\n", emptySlots);
    printf("Активных ячеек: %d\n", activeSlots);
    printf("Удаленных ячеек: %d\n", deletedSlots);
    printf("Общий коэффициент заполнения: %.2f\n", 
           (double)(activeSlots + deletedSlots) / hashTable->size);
}

 
void freeHashTableOA(HashTableOA* hashTable) {
    free(hashTable->table);
    free(hashTable);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация хеш-таблицы с открытой адресацией ===\n");
    printf("Используется двойное хеширование: h(k,i) = (h1(k) + i * h2(k)) mod m\n");
    printf("h1(k) = k mod m, h2(k) = 7 - (k mod 7)\n\n");
    
    HashTableOA* hashTable = createHashTableOA(INITIAL_SIZE);
    
     
    printf("Вставляем элементы:\n");
    int keys[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int values[] = {100, 220, 310, 40, 150, 280, 170, 880, 590};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        printf("Вставляем ключ %d со значением %d\n", keys[i], values[i]);
        insertOA(hashTable, keys[i], values[i]);
        
        if (i % 3 == 2 || i == n - 1) {
            printHashTableOA(hashTable);
        }
    }
    
    printStatisticsOA(hashTable);
    
     
    demonstrateSearch(hashTable, 28);
    demonstrateSearch(hashTable, 99);
    
     
    printf("\nПоиск элементов:\n");
    int searchKeys[] = {22, 17, 99, 4, 100};
    for (int i = 0; i < 5; i++) {
        int found;
        int value = searchOA(hashTable, searchKeys[i], &found);
        if (found) {
            printf("Ключ %d найден, значение: %d\n", searchKeys[i], value);
        } else {
            printf("Ключ %d не найден\n", searchKeys[i]);
        }
    }
    
     
    printf("\nУдаление элементов:\n");
    int deleteKeys[] = {22, 88, 999};
    for (int i = 0; i < 3; i++) {
        if (deleteKeyOA(hashTable, deleteKeys[i])) {
            printf("Ключ %d успешно удален\n", deleteKeys[i]);
        } else {
            printf("Ключ %d не найден для удаления\n", deleteKeys[i]);
        }
    }
    
    printHashTableOA(hashTable);
    printStatisticsOA(hashTable);
    
     
    printf("\nПоиск удаленного элемента:\n");
    demonstrateSearch(hashTable, 22);
    
     
    freeHashTableOA(hashTable);
    
    return 0;
} 
