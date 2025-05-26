 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

 
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

 
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

 
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

 
Node* deleteByValue(Node* head, int value) {
    if (head == NULL) {
        return NULL;
    }
    
     
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    
    return head;
}

 
int search(Node* head, int value) {
    Node* current = head;
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

 
void printList(Node* head) {
    Node* current = head;
    printf("Список: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

 
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация односвязного списка ===\n");
    
    Node* head = NULL;
    
     
    head = insertAtBeginning(head, 10);
    head = insertAtBeginning(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    printList(head);
    
     
    int pos = search(head, 30);
    if (pos != -1) {
        printf("Элемент 30 найден на позиции: %d\n", pos);
    }
    
     
    printf("Удаляем элемент 20\n");
    head = deleteByValue(head, 20);
    printList(head);
    
    printf("Удаляем элемент 40\n");
    head = deleteByValue(head, 40);
    printList(head);
    
     
    freeList(head);
    
    return 0;
} 
