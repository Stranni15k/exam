 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

struct RingNode {
    int data;
    struct RingNode* next;
};

typedef struct RingNode RingNode;

 
RingNode* createRingNode(int data) {
    RingNode* newNode = (RingNode*)malloc(sizeof(RingNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

 
RingNode* insertAtEnd(RingNode* head, int data) {
    RingNode* newNode = createRingNode(data);
    
    if (head == NULL) {
        newNode->next = newNode;  
        return newNode;
    }
    
    RingNode* current = head;
    while (current->next != head) {
        current = current->next;
    }
    
    current->next = newNode;
    newNode->next = head;
    
    return head;
}

 
RingNode* findMiddle(RingNode* head) {
    if (head == NULL) {
        return NULL;
    }
    
    RingNode* slow = head;     
    RingNode* fast = head;     
    RingNode* prev = NULL;
    
     
    do {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    } while (fast != head && fast->next != head);
    
    return prev;  
}

 
RingNode* insertInMiddle(RingNode* head, int data) {
    if (head == NULL) {
        return insertAtEnd(head, data);
    }
    
    RingNode* beforeMiddle = findMiddle(head);
    RingNode* newNode = createRingNode(data);
    
    newNode->next = beforeMiddle->next;
    beforeMiddle->next = newNode;
    
    return head;
}

 
RingNode* deleteByValue(RingNode* head, int value) {
    if (head == NULL) {
        return NULL;
    }
    
     
    if (head->next == head) {
        if (head->data == value) {
            free(head);
            return NULL;
        }
        return head;
    }
    
     
    if (head->data == value) {
        RingNode* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = head->next;
        RingNode* newHead = head->next;
        free(head);
        return newHead;
    }
    
     
    RingNode* current = head;
    while (current->next != head && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next->data == value) {
        RingNode* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    
    return head;
}

 
void printRingList(RingNode* head) {
    if (head == NULL) {
        printf("Кольцевой список пуст\n");
        return;
    }
    
    RingNode* current = head;
    printf("Кольцевой список: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("(цикл)\n");
}

 
void demonstrateTortoiseHare(RingNode* head) {
    if (head == NULL) {
        printf("Список пуст для демонстрации алгоритма\n");
        return;
    }
    
    printf("Демонстрация алгоритма 'черепаха и заяц':\n");
    RingNode* slow = head;
    RingNode* fast = head;
    int steps = 0;
    
    printf("Шаг %d: Черепаха=%d, Заяц=%d\n", steps, slow->data, fast->data);
    
    do {
        slow = slow->next;
        fast = fast->next->next;
        steps++;
        printf("Шаг %d: Черепаха=%d, Заяц=%d\n", steps, slow->data, fast->data);
    } while (fast != head && fast->next != head && steps < 10);
    
    printf("Середина найдена около позиции черепахи\n");
}

 
void freeRingList(RingNode* head) {
    if (head == NULL) {
        return;
    }
    
    RingNode* current = head->next;
    while (current != head) {
        RingNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(head);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация кольцевого списка ===\n");
    
    RingNode* head = NULL;
    
     
    head = insertAtEnd(head, 1);
    head = insertAtEnd(head, 2);
    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 4);
    head = insertAtEnd(head, 5);
    head = insertAtEnd(head, 6);
    
    printRingList(head);
    
     
    demonstrateTortoiseHare(head);
    
     
    printf("\nВставляем элемент 99 в середину:\n");
    head = insertInMiddle(head, 99);
    printRingList(head);
    
     
    printf("Удаляем элемент 3:\n");
    head = deleteByValue(head, 3);
    printRingList(head);
    
    printf("Удаляем головной элемент 1:\n");
    head = deleteByValue(head, 1);
    printRingList(head);
    
     
    freeRingList(head);
    
    return 0;
} 
