#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

class RingNode {
public:
    int data;
    RingNode* next;

    RingNode(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    RingNode* head;

public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        freeList();
    }

    void insertAtEnd(int data) {
        RingNode* newNode = new RingNode(data);
        if (!head) {
            newNode->next = newNode;
            head = newNode;
            return;
        }
        RingNode* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }

    void insertInMiddle(int data) {
        if (!head) {
            insertAtEnd(data);
            return;
        }
        RingNode* slow = head;
        RingNode* fast = head;
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }
        RingNode* newNode = new RingNode(data);
        newNode->next = slow->next;
        slow->next = newNode;
    }

    void deleteByValue(int value) {
        if (!head) return;

        // ���� ������ �������� ������ ���� ����
        if (head->next == head && head->data == value) {
            delete head;
            head = nullptr;
            return;
        }

        // ���� ��������� �������� �������
        if (head->data == value) {
            RingNode* current = head;
            while (current->next != head) {
                current = current->next;
            }
            RingNode* temp = head;
            current->next = head->next;
            head = head->next;
            delete temp;
            return;
        }

        // �������� ���� � �������� ��� � �����
        RingNode* current = head;
        while (current->next != head && current->next->data != value) {
            current = current->next;
        }
        if (current->next->data == value) {
            RingNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    void printList() const {
        if (!head) {
            std::cout << "��������� ������ ����\n";
            return;
        }
        RingNode* current = head;
        std::cout << "��������� ������: ";
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << "(����)\n";
    }

    void demonstrateTortoiseHare() const {
        if (!head) {
            std::cout << "������ ���� ��� ������������ ���������\n";
            return;
        }
        std::cout << "������������ ��������� '�������� � ����':\n";
        RingNode* slow = head;
        RingNode* fast = head;
        int steps = 0;
        std::cout << "��� " << steps << ": ��������=" << slow->data << ", ����=" << fast->data << "\n";
        do {
            slow = slow->next;
            fast = fast->next->next;
            steps++;
            std::cout << "��� " << steps << ": ��������=" << slow->data << ", ����=" << fast->data << "\n";
        } while (fast != head && fast->next != head && steps < 10);
        std::cout << "�������� ������� ����� ������� ��������\n";
    }

    void freeList() {
        if (!head) return;
        RingNode* current = head->next;
        while (current != head) {
            RingNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }
};

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    std::cout << "=== ������������ ���������� ������ ===\n";

    CircularLinkedList list;

    // ������� ���������
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    list.insertAtEnd(6);

    list.printList();

    // ������������ ��������� "�������� � ����"
    list.demonstrateTortoiseHare();

    // ������� � ��������
    std::cout << "\n��������� ������� 99 � ��������:\n";
    list.insertInMiddle(99);
    list.printList();

    // �������� ��������
    std::cout << "������� ������� 3:\n";
    list.deleteByValue(3);
    list.printList();

    std::cout << "������� �������� ������� 1:\n";
    list.deleteByValue(1);
    list.printList();

    return 0;
}
