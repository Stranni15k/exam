/*
 * КОЛЬЦЕВОЙ ОДНОСВЯЗНЫЙ СПИСОК (Circular Linked List)
 * 
 * Особенности:
 * - Последний элемент ссылается на первый (образуется кольцо)
 * - Нет NULL указателей (кроме пустого списка)
 * - Можно обходить бесконечно
 * - Удобен для циклических структур данных
 * 
 * Алгоритм "черепаха и заяц" для поиска середины:
 * - Два указателя: медленный (шаг 1) и быстрый (шаг 2)
 * - Когда быстрый дойдет до конца, медленный будет в середине
 * 
 * Сложность операций:
 * - Добавление в конец: O(n) - нужно найти последний элемент
 * - Поиск середины: O(n/2) = O(n)
 * - Добавление в середину: O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Узел кольцевого списка
typedef struct Node {
    int data;              // Данные узла
    struct Node* next;     // Указатель на следующий узел (никогда не NULL в кольце)
} Node;

// Структура кольцевого списка
typedef struct RingList {
    Node* head;    // Указатель на первый элемент
    int size;      // Размер списка
} RingList;

RingList* createRingList() {
    RingList* list = (RingList*)malloc(sizeof(RingList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void addToEnd(RingList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode;
    } else {
        Node* current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head;
    }
    list->size++;
}

// Поиск середины списка алгоритмом "черепаха и заяц"
int findMiddle(RingList* list) {
    if (list->head == NULL) return -1;  // Пустой список
    
    Node* slow = list->head;  // "Черепаха" - движется на 1 шаг
    Node* fast = list->head;  // "Заяц" - движется на 2 шага
    
    // Двигаем указатели с разной скоростью
    for (int i = 0; i < list->size / 2; i++) {
        slow = slow->next;        // Черепаха: +1 шаг
        fast = fast->next->next;  // Заяц: +2 шага
    }
    
    return slow->data;  // Черепаха указывает на середину
}

void addToMiddle(RingList* list, int value) {
    if (list->head == NULL) {
        addToEnd(list, value);
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    
    Node* slow = list->head;
    Node* prev = NULL;
    
    for (int i = 0; i < list->size / 2; i++) {
        prev = slow;
        slow = slow->next;
    }
    
    prev->next = newNode;
    newNode->next = slow;
    list->size++;
}

void printList(RingList* list) {
    if (list->head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    Node* current = list->head;
    printf("Кольцевой список (размер: %d): ", list->size);
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Кольцевой односвязный список ===\n");
    
    RingList* list = createRingList();
    
    addToEnd(list, 1);
    addToEnd(list, 2);
    addToEnd(list, 4);
    addToEnd(list, 5);
    
    printList(list);
    
    printf("Элемент в середине: %d\n", findMiddle(list));
    
    printf("Добавляем 3 в середину...\n");
    addToMiddle(list, 3);
    
    printList(list);
    
    return 0;
} 