/*
 * ХЭШ-ТАБЛИЦА С МЕТОДОМ ЦЕПОЧЕК (Hash Table with Chaining)
 * 
 * Принцип работы:
 * - Используем хэш-функцию для вычисления индекса
 * - При коллизиях (одинаковые хэши) создаем цепочку элементов
 * - Каждая ячейка таблицы - это указатель на список элементов
 * 
 * Преимущества:
 * - Простая реализация
 * - Хорошо работает при высоком коэффициенте загрузки
 * - Удаление элементов простое
 * 
 * Недостатки:
 * - Дополнительная память для указателей
 * - Плохая локальность данных
 * 
 * Автоматическое перехэширование при коэффициенте загрузки > 0.7
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Узел цепочки в хэш-таблице
typedef struct Node {
    int key;              // Ключ
    int value;            // Значение
    struct Node* next;    // Указатель на следующий элемент в цепочке
} Node;

// Структура хэш-таблицы
typedef struct HashTable {
    Node** table;   // Массив указателей на цепочки
    int size;       // Размер таблицы
    int count;      // Количество элементов
} HashTable;

// Простая хэш-функция: деление с остатком
int hash(int key, int size) {
    return key % size;  // Возвращаем остаток от деления - индекс в таблице
}

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->table = (Node**)calloc(size, sizeof(Node*));
    return ht;
}

void rehash(HashTable** ht) {
    HashTable* oldHt = *ht;
    HashTable* newHt = createHashTable(oldHt->size * 2);
    
    printf("Перехэширование: увеличиваем размер с %d до %d\n", oldHt->size, newHt->size);
    
    for (int i = 0; i < oldHt->size; i++) {
        Node* current = oldHt->table[i];
        while (current != NULL) {
            int index = hash(current->key, newHt->size);
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->key = current->key;
            newNode->value = current->value;
            newNode->next = newHt->table[index];
            newHt->table[index] = newNode;
            newHt->count++;
            current = current->next;
        }
    }
    
    for (int i = 0; i < oldHt->size; i++) {
        Node* current = oldHt->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
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
    
    int index = hash(key, (*ht)->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = (*ht)->table[index];
    (*ht)->table[index] = newNode;
    (*ht)->count++;
}

int search(HashTable* ht, int key) {
    int index = hash(key, ht->size);
    Node* current = ht->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void printHashTable(HashTable* ht) {
    printf("Хэш-таблица (размер: %d, элементов: %d):\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        printf("[%d]: ", i);
        Node* current = ht->table[i];
        while (current != NULL) {
            printf("(%d,%d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Хэш-таблица с методом цепочек ===\n");
    
    HashTable* ht = createHashTable(5);
    
    insert(&ht, 1, 10);
    insert(&ht, 2, 20);
    insert(&ht, 6, 60);
    insert(&ht, 7, 70);
    printHashTable(ht);
    
    printf("\nПоиск ключа 6: %d\n", search(ht, 6));
    
    printf("\nДобавляем больше элементов для демонстрации перехэширования:\n");
    insert(&ht, 11, 110);
    insert(&ht, 12, 120);
    
    printHashTable(ht);
    
    return 0;
} 