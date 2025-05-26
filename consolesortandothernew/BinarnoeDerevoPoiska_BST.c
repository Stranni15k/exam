/*
 * БИНАРНОЕ ДЕРЕВО ПОИСКА (Binary Search Tree)
 * 
 * Свойство BST:
 * - Левое поддерево содержит элементы меньше корня
 * - Правое поддерево содержит элементы больше корня
 * - Это свойство выполняется для всех узлов
 * 
 * Сложность операций (для сбалансированного дерева):
 * - Поиск: O(log n)
 * - Вставка: O(log n)  
 * - Удаление: O(log n)
 * В худшем случае (вырожденное дерево): O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Узел бинарного дерева поиска
typedef struct Node {
    int data;              // Данные узла
    struct Node* left;     // Указатель на левое поддерево (меньшие элементы)
    struct Node* right;    // Указатель на правое поддерево (большие элементы)
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Рекурсивная вставка элемента в BST
Node* insert(Node* root, int data) {
    // Базовый случай: если узел пустой, создаем новый
    if (root == NULL) {
        return createNode(data);
    }
    
    // Рекурсивно вставляем в соответствующее поддерево
    if (data < root->data) {
        // Элемент меньше текущего - идем в левое поддерево
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        // Элемент больше текущего - идем в правое поддерево
        root->right = insert(root->right, data);
    }
    // Если элемент равен текущему - не вставляем (избегаем дублей)
    
    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printTree(Node* root, const char* prefix, int isLast) {
    if (root != NULL) {
        printf("%s", prefix);
        printf("%s", isLast ? "+-- " : "+-- ");
        printf("%d\n", root->data);
        
        char newPrefix[100];
        sprintf_s(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "|   ");
        
        if (root->left != NULL || root->right != NULL) {
            if (root->right != NULL) {
                printTree(root->right, newPrefix, root->left == NULL);
            }
            if (root->left != NULL) {
                printTree(root->left, newPrefix, 1);
            }
        }
    }
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Бинарное дерево поиска ===\n");
    
    Node* root = NULL;
    
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("Дерево:\n");
    printTree(root, "", 1);
    
    printf("\nОбход в порядке возрастания: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("\nУдаляем узел 30...\n");
    root = deleteNode(root, 30);
    
    printf("Дерево после удаления:\n");
    printTree(root, "", 1);
    
    return 0;
} 