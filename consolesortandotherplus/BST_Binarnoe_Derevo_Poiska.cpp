#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createTreeNode(int data) {
    TreeNode* node = new TreeNode{ data, nullptr, nullptr };
    return node;
}

TreeNode* insert(TreeNode* root, int data) {
    if (!root) return createTreeNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

TreeNode* findMin(TreeNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int data) {
    if (!root) return nullptr;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

TreeNode* search(TreeNode* root, int data) {
    if (!root || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    return search(root->right, data);
}

void printTree(TreeNode* root, int depth = 0) {
    if (!root) return;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << root->data << "\n";

    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root) {
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
    }
}

void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация бинарного дерева поиска ===\n";

    TreeNode* root = nullptr;
    int values[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };
    int n = sizeof(values) / sizeof(values[0]);

    std::cout << "Вставляем элементы: ";
    for (int i = 0; i < n; i++) {
        std::cout << values[i] << " ";
        root = insert(root, values[i]);
    }
    std::cout << "\n\n";

    std::cout << "Структура дерева (отступами):\n";
    printTree(root);
    std::cout << "\n";

    std::cout << "Обход in-order: ";
    inorder(root);
    std::cout << "\n";

    std::cout << "Обход pre-order: ";
    preorder(root);
    std::cout << "\n";

    std::cout << "Обход post-order: ";
    postorder(root);
    std::cout << "\n";

    int searchVal = 35;
    TreeNode* found = search(root, searchVal);
    std::cout << "\nПоиск: ";
    if (found)
        std::cout << "Элемент " << searchVal << " найден\n";
    else
        std::cout << "Элемент " << searchVal << " не найден\n";

    std::cout << "\nУдаляем 30:\n";
    root = deleteNode(root, 30);
    printTree(root);

    std::cout << "\nУдаляем 50 (корень):\n";
    root = deleteNode(root, 50);
    printTree(root);

    std::cout << "\nОбход in-order после удалений: ";
    inorder(root);
    std::cout << "\n";

    freeTree(root);
    return 0;
}
