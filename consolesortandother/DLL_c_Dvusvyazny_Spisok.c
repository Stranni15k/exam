 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

struct DoublyNode {
    int data;
    struct DoublyNode* next;
    struct DoublyNode* prev;
};

typedef struct DoublyNode DoublyNode;

 
DoublyNode* createDoublyNode(int data) {
    DoublyNode* newNode = (DoublyNode*)malloc(sizeof(DoublyNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

 
DoublyNode* insertAtEnd(DoublyNode* head, int data) {
    DoublyNode* newNode = createDoublyNode(data);
    
    if (head == NULL) {
        return newNode;
    }
    
    DoublyNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
    newNode->prev = current;
    
    return head;
}

 
DoublyNode* deleteByValue(DoublyNode* head, int value) {
    if (head == NULL) {
        return NULL;
    }
    
    DoublyNode* current = head;
    
     
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    
    if (current == NULL) {
        return head;  
    }
    
     
    if (current->prev == NULL && current->next == NULL) {
        free(current);
        return NULL;
    }
    
     
    if (current->prev == NULL) {
        head = current->next;
        head->prev = NULL;
    }
     
    else if (current->next == NULL) {
        current->prev->next = NULL;
    }
     
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    
    free(current);
    return head;
}

 
int search(DoublyNode* head, int value) {
    DoublyNode* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;  
}

 
void printListForward(DoublyNode* head) {
    DoublyNode* current = head;
    printf("Список (вперед): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

 
void printListBackward(DoublyNode* head) {
    if (head == NULL) {
        printf("Список (назад): пустой\n");
        return;
    }
    
     
    DoublyNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    printf("Список (назад): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

 
void freeDoublyList(DoublyNode* head) {
    DoublyNode* current = head;
    while (current != NULL) {
        DoublyNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация двусвязного списка ===\n");
    
    DoublyNode* head = NULL;
    
     
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    head = insertAtEnd(head, 50);
    
    printListForward(head);
    printListBackward(head);
    
     
    int pos = search(head, 30);
    if (pos != -1) {
        printf("Элемент 30 найден на позиции: %d\n", pos);
    }
    
     
    printf("Удаляем элемент 20\n");
    head = deleteByValue(head, 20);
    printListForward(head);
    
    printf("Удаляем элемент 50 (последний)\n");
    head = deleteByValue(head, 50);
    printListForward(head);
    
    printf("Удаляем элемент 10 (первый)\n");
    head = deleteByValue(head, 10);
    printListForward(head);
    printListBackward(head);
    
     
    freeDoublyList(head);
    
    return 0;
} 
