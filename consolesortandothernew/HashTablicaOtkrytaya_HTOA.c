/*
 * ХЭШ-ТАБЛИЦА С ОТКРЫТОЙ АДРЕСАЦИЕЙ (Open Addressing Hash Table)
 * 
 * Принцип работы:
 * - Все элементы хранятся в самой таблице (без цепочек)
 * - При коллизии ищем следующую свободную ячейку
 * - Используем двойное хэширование для поиска
 * 
 * Двойное хэширование:
 * - hash(key, i) = (hash1(key) + i * hash2(key)) % size
 * - hash1(key) = key % size (первичная хэш-функция)
 * - hash2(key) = 7 - (key % 7) (вторичная хэш-функция)
 * 
 * Преимущества:
 * - Лучшая локальность данных
 * - Нет дополнительной памяти для указателей
 * - Хороший performance при низком коэффициенте загрузки
 * 
 * Недостатки:
 * - Сложное удаление (нужны флаги isDeleted)
 * - Производительность падает при высокой загрузке
 * - Нужно перехэширование при заполнении
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Элемент хэш-таблицы
typedef struct HashEntry {
    int key;           // Ключ
    int value;         // Значение
    int isOccupied;    // Занята ли ячейка
    int isDeleted;     // Помечена ли ячейка как удаленная
} HashEntry;

// Структура хэш-таблицы
typedef struct HashTable {
    HashEntry* table;  // Массив элементов
    int size;          // Размер таблицы
    int count;         // Количество элементов
} HashTable;

// Первичная хэш-функция
int hash1(int key, int size) {
    return key % size;  // Простое деление с остатком
}

// Вторичная хэш-функция (должна быть взаимно простой с размером таблицы)
int hash2(int key) {
    return 7 - (key % 7);  // Используем простое число 7
}

// Двойное хэширование: комбинирует две хэш-функции
int doubleHash(int key, int size, int i) {
    return (hash1(key, size) + i * hash2(key)) % size;  // i - номер попытки
}

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->table = (HashEntry*)calloc(size, sizeof(HashEntry));
    return ht;
}

void rehash(HashTable** ht) {
    HashTable* oldHt = *ht;
    HashTable* newHt = createHashTable(oldHt->size * 2);
    
    printf("Перехэширование: увеличиваем размер с %d до %d\n", oldHt->size, newHt->size);
    
    for (int i = 0; i < oldHt->size; i++) {
        if (oldHt->table[i].isOccupied && !oldHt->table[i].isDeleted) {
            int key = oldHt->table[i].key;
            int value = oldHt->table[i].value;
            
            for (int j = 0; j < newHt->size; j++) {
                int index = doubleHash(key, newHt->size, j);
                if (!newHt->table[index].isOccupied) {
                    newHt->table[index].key = key;
                    newHt->table[index].value = value;
                    newHt->table[index].isOccupied = 1;
                    newHt->table[index].isDeleted = 0;
                    newHt->count++;
                    break;
                }
            }
        }
    }
    
    free(oldHt->table);
    free(oldHt);
    *ht = newHt;
}

void insert(HashTable** ht, int key, int value) {
    if ((float)(*ht)->count / (*ht)->size > 0.7) {
        rehash(ht);
    }
    
    for (int i = 0; i < (*ht)->size; i++) {
        int index = doubleHash(key, (*ht)->size, i);
        
        if (!(*ht)->table[index].isOccupied || (*ht)->table[index].isDeleted) {
            (*ht)->table[index].key = key;
            (*ht)->table[index].value = value;
            (*ht)->table[index].isOccupied = 1;
            (*ht)->table[index].isDeleted = 0;
            (*ht)->count++;
            return;
        }
        
        if ((*ht)->table[index].key == key) {
            (*ht)->table[index].value = value;
            return;
        }
    }
}

int search(HashTable* ht, int key) {
    for (int i = 0; i < ht->size; i++) {
        int index = doubleHash(key, ht->size, i);
        
        if (!ht->table[index].isOccupied) {
            return -1;
        }
        
        if (ht->table[index].key == key && !ht->table[index].isDeleted) {
            return ht->table[index].value;
        }
    }
    return -1;
}

void delete(HashTable* ht, int key) {
    for (int i = 0; i < ht->size; i++) {
        int index = doubleHash(key, ht->size, i);
        
        if (!ht->table[index].isOccupied) {
            return;
        }
        
        if (ht->table[index].key == key && !ht->table[index].isDeleted) {
            ht->table[index].isDeleted = 1;
            ht->count--;
            return;
        }
    }
}

void printHashTable(HashTable* ht) {
    printf("Хэш-таблица (размер: %d, элементов: %d):\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        printf("[%d]: ", i);
        if (ht->table[i].isOccupied && !ht->table[i].isDeleted) {
            printf("(%d,%d)", ht->table[i].key, ht->table[i].value);
        } else if (ht->table[i].isDeleted) {
            printf("DELETED");
        } else {
            printf("EMPTY");
        }
        printf("\n");
    }
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Хэш-таблица с открытой адресацией ===\n");
    
    HashTable* ht = createHashTable(11);
    
    insert(&ht, 10, 100);
    insert(&ht, 22, 220);
    insert(&ht, 31, 310);
    insert(&ht, 4, 40);
    insert(&ht, 15, 150);
    
    printHashTable(ht);
    
    printf("\nПоиск ключа 22: %d\n", search(ht, 22));
    
    printf("\nУдаляем ключ 22\n");
    delete(ht, 22);
    
    printHashTable(ht);
    
    printf("\nДобавляем больше элементов для демонстрации перехэширования:\n");
    insert(&ht, 6, 60);
    insert(&ht, 7, 70);
    insert(&ht, 8, 80);
    insert(&ht, 9, 90);
    
    printHashTable(ht);
    
    return 0;
}