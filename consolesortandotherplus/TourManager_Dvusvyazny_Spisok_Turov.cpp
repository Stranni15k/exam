#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

struct Tour {
    int id;
    std::string name;
    std::string country;
    int places;
    std::string responsible;
};

struct TourNode {
    Tour tour;
    TourNode* next;
    TourNode* prev;
};

TourNode* head = nullptr;

TourNode* createNode(int id, const std::string& name, const std::string& country, int places, const std::string& responsible) {
    TourNode* node = new TourNode;
    node->tour = { id, name, country, places, responsible };
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void insertSortedById(int id, const std::string& name, const std::string& country, int places, const std::string& responsible) {
    TourNode* newNode = createNode(id, name, country, places, responsible);

    if (!head || id < head->tour.id) {
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        return;
    }

    TourNode* current = head;
    while (current->next && current->next->tour.id < id) {
        current = current->next;
    }

    if (current->tour.id == id || (current->next && current->next->tour.id == id)) {
        std::cout << "Тур с таким ID уже существует.\n";
        delete newNode;
        return;
    }

    newNode->next = current->next;
    if (current->next) current->next->prev = newNode;
    current->next = newNode;
    newNode->prev = current;
}

void printTours() {
    if (!head) {
        std::cout << "Список пуст.\n";
        return;
    }

    TourNode* current = head;
    while (current) {
        std::cout << "ID: " << current->tour.id << "\n";
        std::cout << "Название: " << current->tour.name << "\n";
        std::cout << "Страна: " << current->tour.country << "\n";
        std::cout << "Места: " << current->tour.places << "\n";
        std::cout << "Ответственный: " << current->tour.responsible << "\n\n";
        current = current->next;
    }
}

void printTourById(int id) {
    TourNode* current = head;
    while (current) {
        if (current->tour.id == id) {
            std::cout << "Найден тур с ID " << id << ":\n";
            std::cout << "Название: " << current->tour.name << "\n";
            std::cout << "Страна: " << current->tour.country << "\n";
            std::cout << "Места: " << current->tour.places << "\n";
            std::cout << "Ответственный: " << current->tour.responsible << "\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Тур с ID " << id << " не найден.\n";
}

void deleteTour(int id) {
    TourNode* current = head;
    while (current) {
        if (current->tour.id == id) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next;
            if (current->next) current->next->prev = current->prev;
            delete current;
            std::cout << "Тур удалён.\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Тур не найден.\n";
}

void searchByCountry(const std::string& country) {
    bool found = false;
    TourNode* current = head;
    while (current) {
        if (current->tour.country == country) {
            std::cout << "ID: " << current->tour.id << ", Название: " << current->tour.name << "\n";
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        std::cout << "Нет туров в указанной стране.\n";
    }
}

void showStatistics() {
    if (!head) {
        std::cout << "Список пуст.\n";
        return;
    }

    int total = 0, sum = 0, min = 1e9, max = 0;
    TourNode* current = head;
    while (current) {
        total++;
        sum += current->tour.places;
        if (current->tour.places < min) min = current->tour.places;
        if (current->tour.places > max) max = current->tour.places;
        current = current->next;
    }

    std::cout << "Всего туров: " << total << "\n";
    std::cout << "Всего мест: " << sum << "\n";
    std::cout << "Среднее: " << (double)sum / total << "\n";
    std::cout << "Минимум мест: " << min << "\n";
    std::cout << "Максимум мест: " << max << "\n";
}

void freeAll() {
    while (head) {
        TourNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    int choice;
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить тур\n";
        std::cout << "2. Показать все туры\n";
        std::cout << "3. Найти тур по ID\n";
        std::cout << "4. Удалить тур по ID\n";
        std::cout << "5. Поиск по стране\n";
        std::cout << "6. Показать статистику\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        int id, places;
        std::string name, country, responsible;

        switch (choice) {
        case 1:
            std::cout << "ID: ";
            if (!(std::cin >> id)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод ID.\n";
                break;
            }
            std::cin.ignore();
            std::cout << "Название: ";
            std::getline(std::cin, name);
            std::cout << "Страна: ";
            std::getline(std::cin, country);
            std::cout << "Места: ";
            if (!(std::cin >> places)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод ID.\n";
                break;
            }
            std::cin.ignore();
            std::cout << "Ответственный: ";
            std::getline(std::cin, responsible);
            insertSortedById(id, name, country, places, responsible);
            break;

        case 2:
            printTours();
            break;

        case 3:
            std::cout << "Введите ID: ";
            std::cin >> id;
            std::cin.ignore();
            printTourById(id);
            break;

        case 4:
            std::cout << "Введите ID для удаления: ";
            std::cin >> id;
            std::cin.ignore();
            deleteTour(id);
            break;

        case 5:
            std::cout << "Введите страну: ";
            std::getline(std::cin, country);
            searchByCountry(country);
            break;

        case 6:
            showStatistics();
            break;

        case 0:
            freeAll();
            return 0;

        default:
            std::cout << "Неверный ввод.\n";
        }
    }

