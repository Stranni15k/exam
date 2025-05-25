#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        freeList();
    }

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }

    void deleteByValue(int value) {
        if (!head) return;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data != value)
            current = current->next;

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    int search(int value) const {
        Node* current = head;
        int position = 0;
        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        return -1;
    }

    void printList() const {
        Node* current = head;
        std::cout << "Список: ";
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    void freeList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main() {
    #ifdef _WIN32
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
    #endif
    std::cout << "=== Демонстрация односвязного списка (C++) ===\n";

    SinglyLinkedList list;

    // Вставка элементов
    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    list.printList();

    // Поиск
    int pos = list.search(30);
    if (pos != -1) {
        std::cout << "Элемент 30 найден на позиции: " << pos << "\n";
    }

    // Удаление
    std::cout << "Удаляем элемент 20\n";
    list.deleteByValue(20);
    list.printList();

    std::cout << "Удаляем элемент 40\n";
    list.deleteByValue(40);
    list.printList();

    return 0;
}
