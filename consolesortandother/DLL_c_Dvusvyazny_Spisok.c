#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_STRING_LENGTH 256

struct Tour {
    int id;
    char name[MAX_STRING_LENGTH];
    char country[MAX_STRING_LENGTH];
    int places;
    char responsible[MAX_STRING_LENGTH];
};

struct TourNode {
    struct Tour tour;
    struct TourNode* next;
    struct TourNode* prev;
};

typedef struct Tour Tour;
typedef struct TourNode TourNode;

TourNode* head = NULL;

TourNode* createTourNode(int id, const char* name, const char* country, int places, const char* responsible) {
    TourNode* newNode = (TourNode*)malloc(sizeof(TourNode));
    
    newNode->tour.id = id;
    strncpy_s(newNode->tour.name, MAX_STRING_LENGTH, name, MAX_STRING_LENGTH - 1);
    strncpy_s(newNode->tour.country, MAX_STRING_LENGTH, country, MAX_STRING_LENGTH - 1);
    newNode->tour.places = places;
    strncpy_s(newNode->tour.responsible, MAX_STRING_LENGTH, responsible, MAX_STRING_LENGTH - 1);
    
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}

void addTour(int id, const char* name, const char* country, int places, const char* responsible) {
    TourNode* current = head;
    while (current != NULL) {
        if (current->tour.id == id) {
            printf("Ошибка: Тур с ID %d уже существует!\n", id);
            return;
        }
        current = current->next;
    }
    
    TourNode* newNode = createTourNode(id, name, country, places, responsible);
    
    if (head == NULL) {
        head = newNode;
        printf("Тур добавлен как первый элемент списка\n");
        return;
    }
    
    current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
    newNode->prev = current;
    
    printf("Тур успешно добавлен!\n");
}

void sortToursByID() {
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    int swapped;
    TourNode* current;
    TourNode* last = NULL;
    
    do {
        swapped = 0;
        current = head;
        
        while (current->next != last) {
            if (current->tour.id > current->next->tour.id) {
                Tour temp = current->tour;
                current->tour = current->next->tour;
                current->next->tour = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void printAllToursOrdered() {
    if (head == NULL) {
        printf("Список туров пуст\n");
        return;
    }
    
    sortToursByID();
    
    printf("\n=== Список всех туров (упорядочен по ID) ===\n");
    printf("%-5s %-30s %-20s %-8s %-30s\n", "ID", "Название", "Страна", "Места", "Ответственный");
    printf("====================================================================================\n");
    
    TourNode* current = head;
    while (current != NULL) {
        printf("%-5d %-30s %-20s %-8d %-30s\n", 
               current->tour.id, 
               current->tour.name, 
               current->tour.country, 
               current->tour.places, 
               current->tour.responsible);
        current = current->next;
    }
    printf("\n");
}

void printAllTours() {
    if (head == NULL) {
        printf("Список туров пуст\n");
        return;
    }
    
    printf("\n=== Все туры (в порядке добавления) ===\n");
    printf("%-5s %-30s %-20s %-8s %-30s\n", "ID", "Название", "Страна", "Места", "Ответственный");
    printf("====================================================================================\n");
    
    TourNode* current = head;
    while (current != NULL) {
        printf("%-5d %-30s %-20s %-8d %-30s\n", 
               current->tour.id, 
               current->tour.name, 
               current->tour.country, 
               current->tour.places, 
               current->tour.responsible);
        current = current->next;
    }
    printf("\n");
}

void printTourDetails(int id) {
    TourNode* current = head;
    while (current != NULL) {
        if (current->tour.id == id) {
            printf("\n=== Детали тура ===\n");
            printf("ID: %d\n", current->tour.id);
            printf("Название: %s\n", current->tour.name);
            printf("Страна: %s\n", current->tour.country);
            printf("Количество мест: %d\n", current->tour.places);
            printf("Ответственный: %s\n", current->tour.responsible);
            printf("==================\n");
            return;
        }
        current = current->next;
    }
    printf("Тур с ID %d не найден\n", id);
}

void deleteTour(int id) {
    TourNode* current = head;
    
    while (current != NULL) {
        if (current->tour.id == id) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            
            printf("Тур с ID %d удален\n", id);
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Тур с ID %d не найден\n", id);
}

void searchTourByCountry(const char* country) {
    printf("\n=== Туры в стране: %s ===\n", country);
    printf("%-5s %-30s %-8s %-30s\n", "ID", "Название", "Места", "Ответственный");
    printf("======================================================================\n");
    
    TourNode* current = head;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->tour.country, country) == 0) {
            printf("%-5d %-30s %-8d %-30s\n", 
                   current->tour.id, 
                   current->tour.name, 
                   current->tour.places, 
                   current->tour.responsible);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Туры в стране %s не найдены\n", country);
    }
    printf("\n");
}

void printStatistics() {
    if (head == NULL) {
        printf("Список туров пуст\n");
        return;
    }
    
    int totalTours = 0;
    int totalPlaces = 0;
    int maxPlaces = 0;
    int minPlaces = 999999;
    
    TourNode* current = head;
    while (current != NULL) {
        totalTours++;
        totalPlaces += current->tour.places;
        if (current->tour.places > maxPlaces) {
            maxPlaces = current->tour.places;
        }
        if (current->tour.places < minPlaces) {
            minPlaces = current->tour.places;
        }
        current = current->next;
    }
    
    printf("\n=== Статистика по турам ===\n");
    printf("Общее количество туров: %d\n", totalTours);
    printf("Общее количество мест: %d\n", totalPlaces);
    printf("Среднее количество мест: %.2f\n", (double)totalPlaces / totalTours);
    printf("Максимальное количество мест: %d\n", maxPlaces);
    printf("Минимальное количество мест: %d\n", minPlaces);
    printf("=========================\n\n");
}

void freeAllTours() {
    TourNode* current = head;
    while (current != NULL) {
        TourNode* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

void showMenu() {
    printf("\n=== Система управления турами ===\n");
    printf("1. Добавить тур\n");
    printf("2. Вывести все туры (упорядочено по ID)\n");
    printf("3. Вывести все туры на экран\n");
    printf("4. Найти тур по ID\n");
    printf("5. Удалить тур\n");
    printf("6. Поиск туров по стране\n");
    printf("7. Показать статистику\n");
    printf("0. Выход\n");
    printf("==============================\n");
    printf("Выберите опцию: ");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация двусвязного списка туров ===\n");
    
    addTour(1, "Золотое кольцо", "Россия", 25, "Иванов И.И.");
    addTour(3, "Альпы", "Швейцария", 15, "Петров П.П.");
    addTour(2, "Париж романтический", "Франция", 20, "Сидоров С.С.");
    addTour(5, "Токио экспресс", "Япония", 12, "Танака Х.");
    addTour(4, "Римские каникулы", "Италия", 18, "Россини М.");
    
    printAllTours();
    printAllToursOrdered();
    
    printf("Поиск тура с ID 3:\n");
    printTourDetails(3);
    
    searchTourByCountry("Россия");
    printStatistics();
    
    int choice;
    char name[MAX_STRING_LENGTH], country[MAX_STRING_LENGTH], responsible[MAX_STRING_LENGTH];
    int id, places;
    
    while (1) {
        showMenu();
        scanf_s("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Введите ID тура: ");
                scanf_s("%d", &id);
                printf("Введите название тура: ");
                scanf_s(" %[^\n]", name, MAX_STRING_LENGTH);
                printf("Введите страну: ");
                scanf_s(" %[^\n]", country, MAX_STRING_LENGTH);
                printf("Введите количество мест: ");
                scanf_s("%d", &places);
                printf("Введите ФИО ответственного: ");
                scanf_s(" %[^\n]", responsible, MAX_STRING_LENGTH);
                addTour(id, name, country, places, responsible);
                break;
                
            case 2:
                printAllToursOrdered();
                break;
                
            case 3:
                printAllTours();
                break;
                
            case 4:
                printf("Введите ID тура для поиска: ");
                scanf_s("%d", &id);
                printTourDetails(id);
                break;
                
            case 5:
                printf("Введите ID тура для удаления: ");
                scanf_s("%d", &id);
                deleteTour(id);
                break;
                
            case 6:
                printf("Введите название страны: ");
                scanf_s(" %[^\n]", country, MAX_STRING_LENGTH);
                searchTourByCountry(country);
                break;
                
            case 7:
                printStatistics();
                break;
                
            case 0:
                printf("Выход из программы...\n");
                freeAllTours();
                return 0;
                
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }
    
    return 0;
} 