 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

 
TreeNode* createTreeNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

 
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createTreeNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

 
TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

 
TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
         
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        
         
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

 
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
}

 
void printTree(TreeNode* root, char* prefix, int isLast) {
    if (root == NULL) {
        return;
    }
    
    printf("%s", prefix);
    printf("%s", isLast ? "└── " : "├── ");
    printf("%d\n", root->data);
    
    char newPrefix[256];
    sprintf(newPrefix, "%s%s", prefix, isLast ? "    " : "│   ");
    
    if (root->left != NULL || root->right != NULL) {
        if (root->right != NULL) {
            printTree(root->right, newPrefix, root->left == NULL);
        }
        if (root->left != NULL) {
            printTree(root->left, newPrefix, 1);
        }
    }
}

 
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

 
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

 
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

 
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация бинарного дерева поиска ===\n");
    
    TreeNode* root = NULL;
    
     
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);
    
    printf("Вставляем элементы: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n\n");
    
     
    printf("Структура дерева:\n");
    printTree(root, "", 1);
    printf("\n");
    
     
    printf("Обход in-order (отсортированный): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Обход pre-order: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Обход post-order: ");
    postorderTraversal(root);
    printf("\n\n");
    
     
    int searchValue = 35;
    TreeNode* found = search(root, searchValue);
    if (found) {
        printf("Элемент %d найден в дереве\n", searchValue);
    } else {
        printf("Элемент %d не найден в дереве\n", searchValue);
    }
    
     
    printf("\nУдаляем элемент 30:\n");
    root = deleteNode(root, 30);
    printTree(root, "", 1);
    
    printf("\nУдаляем элемент 50 (корень):\n");
    root = deleteNode(root, 50);
    printTree(root, "", 1);
    
    printf("\nОбход in-order после удалений: ");
    inorderTraversal(root);
    printf("\n");
    
     
    freeTree(root);
    
    return 0;
} 
