 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define INITIAL_SIZE 7
#define LOAD_FACTOR_THRESHOLD 0.75

struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

struct HashTable {
    struct HashNode** table;
    int size;
    int count;
};

typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

 
HashNode* createHashNode(int key, int value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

 
HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->count = 0;
    hashTable->table = (HashNode**)calloc(size, sizeof(HashNode*));
    return hashTable;
}

 
int hash1(int key, int size) {
    return key % size;
}

 
int hash2(int key, int size) {
    return 7 - (key % 7);
}

 
void insert(HashTable* hashTable, int key, int value);

 
void rehash(HashTable* hashTable) {
    printf("Перехеширование: увеличиваем размер с %d до %d\n", hashTable->size, hashTable->size * 2);
    
    HashNode** oldTable = hashTable->table;
    int oldSize = hashTable->size;
    int oldCount = hashTable->count;
    
     
    hashTable->size = oldSize * 2;
    hashTable->count = 0;
    hashTable->table = (HashNode**)calloc(hashTable->size, sizeof(HashNode*));
    
     
    for (int i = 0; i < oldSize; i++) {
        HashNode* current = oldTable[i];
        while (current != NULL) {
            HashNode* next = current->next;
            insert(hashTable, current->key, current->value);
            free(current);
            current = next;
        }
    }
    
    free(oldTable);
    printf("Перехеширование завершено. Новый размер: %d\n", hashTable->size);
}

 
void insert(HashTable* hashTable, int key, int value) {
     
    double loadFactor = (double)hashTable->count / hashTable->size;
    if (loadFactor > LOAD_FACTOR_THRESHOLD) {
        rehash(hashTable);
    }
    
    int index = hash1(key, hashTable->size);
    
     
    HashNode* current = hashTable->table[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;  
            return;
        }
        current = current->next;
    }
    
     
    HashNode* newNode = createHashNode(key, value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    hashTable->count++;
}

 
int search(HashTable* hashTable, int key, int* found) {
    int index = hash1(key, hashTable->size);
    HashNode* current = hashTable->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    *found = 0;
    return -1;
}

 
int deleteKey(HashTable* hashTable, int key) {
    int index = hash1(key, hashTable->size);
    HashNode* current = hashTable->table[index];
    HashNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                hashTable->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            hashTable->count--;
            return 1;  
        }
        prev = current;
        current = current->next;
    }
    
    return 0;  
}

 
void printHashTable(HashTable* hashTable) {
    printf("\nСостояние хеш-таблицы (метод цепочек):\n");
    printf("Размер: %d, Элементов: %d, Коэффициент загрузки: %.2f\n", 
           hashTable->size, hashTable->count, (double)hashTable->count / hashTable->size);
    
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%2d]: ", i);
        HashNode* current = hashTable->table[i];
        if (current == NULL) {
            printf("пусто");
        } else {
            while (current != NULL) {
                printf("(%d:%d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
        }
        printf("\n");
    }
}

 
void printStatistics(HashTable* hashTable) {
    int emptySlots = 0;
    int maxChainLength = 0;
    int totalChainLength = 0;
    
    for (int i = 0; i < hashTable->size; i++) {
        int chainLength = 0;
        HashNode* current = hashTable->table[i];
        
        if (current == NULL) {
            emptySlots++;
        } else {
            while (current != NULL) {
                chainLength++;
                current = current->next;
            }
            totalChainLength += chainLength;
            if (chainLength > maxChainLength) {
                maxChainLength = chainLength;
            }
        }
    }
    
    printf("\nСтатистика:\n");
    printf("Пустых ячеек: %d\n", emptySlots);
    printf("Максимальная длина цепочки: %d\n", maxChainLength);
    printf("Средняя длина цепочки: %.2f\n", 
           hashTable->count > 0 ? (double)totalChainLength / (hashTable->size - emptySlots) : 0.0);
}

 
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        HashNode* current = hashTable->table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация хеш-таблицы с методом цепочек ===\n");
    
    HashTable* hashTable = createHashTable(INITIAL_SIZE);
    
     
    printf("Вставляем элементы:\n");
    int keys[] = {10, 22, 31, 4, 15, 28, 17, 88, 59, 6, 13, 20, 27};
    int values[] = {100, 220, 310, 40, 150, 280, 170, 880, 590, 60, 130, 200, 270};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        printf("Вставляем ключ %d со значением %d\n", keys[i], values[i]);
        insert(hashTable, keys[i], values[i]);
        
        if (i % 5 == 4 || i == n - 1) {
            printHashTable(hashTable);
        }
    }
    
    printStatistics(hashTable);
    
     
    printf("\nПоиск элементов:\n");
    int searchKeys[] = {22, 17, 99, 6, 100};
    for (int i = 0; i < 5; i++) {
        int found;
        int value = search(hashTable, searchKeys[i], &found);
        if (found) {
            printf("Ключ %d найден, значение: %d\n", searchKeys[i], value);
        } else {
            printf("Ключ %d не найден\n", searchKeys[i]);
        }
    }
    
     
    printf("\nУдаление элементов:\n");
    int deleteKeys[] = {22, 88, 999};
    for (int i = 0; i < 3; i++) {
        if (deleteKey(hashTable, deleteKeys[i])) {
            printf("Ключ %d успешно удален\n", deleteKeys[i]);
        } else {
            printf("Ключ %d не найден для удаления\n", deleteKeys[i]);
        }
    }
    
    printHashTable(hashTable);
    printStatistics(hashTable);
    
     
    freeHashTable(hashTable);
    
    return 0;
} 
