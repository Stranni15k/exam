/*
 * СИСТЕМА УПРАВЛЕНИЯ ТУРАМИ - ДВУСВЯЗНЫЙ СПИСОК
 *
 * Особенности:
 * - Каждый узел имеет ссылки на следующий И предыдущий элементы
 * - Автоматическое упорядочивание по уникальному номеру (ID)
 * - Эффективное добавление/удаление в любом месте O(1) при наличии указателя
 * - Поиск по ID O(n) в худшем случае
 *
 * Функции:
 * - Добавление тура с упорядочиванием по ID
 * - Вывод всего списка туров
 * - Поиск тура по ID
 * - Удаление тура
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

 // Структура для хранения информации о туре
typedef struct Tour {
    int id;                    // Уникальный номер (идентификатор)
    char name[100];           // Название тура
    char country[50];         // Страна, в которой проводится тур
    int places;               // Количество мест в туре
    char responsible[100];    // ФИО ответственного за тур
} Tour;

// Узел двусвязного списка
typedef struct Node {
    Tour data;              // Данные о туре
    struct Node* next;      // Указатель на следующий узел
    struct Node* prev;      // Указатель на предыдущий узел
} Node;

// Структура двусвязного списка туров
typedef struct TourList {
    Node* head;             // Указатель на первый элемент
    Node* tail;             // Указатель на последний элемент
    int size;               // Размер списка
} TourList;

// Создание пустого списка туров
TourList* createTourList() {
    TourList* list = (TourList*)malloc(sizeof(TourList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Создание нового узла с данными тура
Node* createNode(Tour tour) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = tour;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Добавление тура в список с упорядочиванием по ID
void addTour(TourList* list, Tour tour) {
    Node* newNode = createNode(tour);

    // Если список пустой
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->size++;
        printf("Тур с ID %d успешно добавлен!\n", tour.id);
        return;
    }

    // Поиск места для вставки (упорядочивание по ID)
    Node* current = list->head;

    // Проверка на дублирование ID
    while (current != NULL) {
        if (current->data.id == tour.id) {
            printf("Ошибка: Тур с ID %d уже существует!\n", tour.id);
            free(newNode);
            return;
        }
        current = current->next;
    }

    current = list->head;

    // Если новый ID меньше первого элемента - вставляем в начало
    if (tour.id < list->head->data.id) {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        list->size++;
        printf("Тур с ID %d успешно добавлен в начало списка!\n", tour.id);
        return;
    }

    // Поиск позиции для вставки
    while (current != NULL && current->data.id < tour.id) {
        if (current->next == NULL || current->next->data.id > tour.id) {
            // Вставляем после current
            newNode->next = current->next;
            newNode->prev = current;

            if (current->next != NULL) {
                current->next->prev = newNode;
            }
            else {
                // Вставляем в конец
                list->tail = newNode;
            }

            current->next = newNode;
            list->size++;
            printf("Тур с ID %d успешно добавлен!\n", tour.id);
            return;
        }
        current = current->next;
    }
}

// Вывод всего списка туров на экран
void printAllTours(TourList* list) {
    if (list->head == NULL) {
        printf("Список туров пуст.\n");
        return;
    }

    printf("\n=== СПИСОК ВСЕХ ТУРОВ (упорядочен по ID) ===\n");
    printf("Всего туров: %d\n\n", list->size);

    Node* current = list->head;
    int counter = 1;

    while (current != NULL) {
        printf("--- Тур #%d ---\n", counter);
        printf("ID: %d\n", current->data.id);
        printf("Название: %s\n", current->data.name);
        printf("Страна: %s\n", current->data.country);
        printf("Количество мест: %d\n", current->data.places);
        printf("Ответственный: %s\n", current->data.responsible);
        printf("----------------------------------------\n");

        current = current->next;
        counter++;
    }
}

// Поиск тура по ID
Tour* findTourById(TourList* list, int id) {
    Node* current = list->head;

    while (current != NULL) {
        if (current->data.id == id) {
            return &(current->data);
        }
        current = current->next;
    }

    return NULL; // Тур не найден
}

// Удаление тура по ID
void removeTourById(TourList* list, int id) {
    Node* current = list->head;

    while (current != NULL) {
        if (current->data.id == id) {
            // Обновляем связи предыдущего узла
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            else {
                list->head = current->next;
            }

            // Обновляем связи следующего узла
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            else {
                list->tail = current->prev;
            }

            free(current);
            list->size--;
            printf("Тур с ID %d успешно удален!\n", id);
            return;
        }
        current = current->next;
    }

    printf("Тур с ID %d не найден!\n", id);
}

// Освобождение памяти списка
void freeTourList(TourList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// Ввод данных тура с клавиатуры
Tour inputTourData() {
    Tour tour;

    printf("\n--- Ввод данных нового тура ---\n");
    printf("Уникальный номер (ID): ");
    scanf_s("%d", &tour.id);

    printf("Название тура: ");
    getchar(); // Очистка буфера
    fgets(tour.name, sizeof(tour.name), stdin);
    tour.name[strcspn(tour.name, "\n")] = 0; // Удаляем символ новой строки

    printf("Страна: ");
    fgets(tour.country, sizeof(tour.country), stdin);
    tour.country[strcspn(tour.country, "\n")] = 0;

    printf("Количество мест: ");
    scanf_s("%d", &tour.places);

    printf("ФИО ответственного: ");
    getchar(); // Очистка буфера
    fgets(tour.responsible, sizeof(tour.responsible), stdin);
    tour.responsible[strcspn(tour.responsible, "\n")] = 0;

    return tour;
}

// Главное меню программы
void showMenu() {
    printf("\n=== СИСТЕМА УПРАВЛЕНИЯ ТУРАМИ ===\n");
    printf("1. Добавить тур\n");
    printf("2. Показать все туры\n");
    printf("3. Найти тур по ID\n");
    printf("4. Удалить тур по ID\n");
    printf("5. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Система управления турами ===\n");
    printf("Используется двусвязный список с упорядочиванием по ID\n");

    TourList* tourList = createTourList();
    int choice;

    // Добавляем несколько примеров для демонстрации
    Tour tour1 = { 101, "Золотое кольцо России", "Россия", 25, "Иванов Иван Иванович" };
    Tour tour2 = { 50, "Тур по Европе", "Франция", 15, "Петров Петр Петрович" };
    Tour tour3 = { 75, "Сафари в Африке", "Кения", 12, "Сидоров Сидор Сидорович" };

    addTour(tourList, tour1);
    addTour(tourList, tour2);
    addTour(tourList, tour3);

    do {
        showMenu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            Tour newTour = inputTourData();
            addTour(tourList, newTour);
            break;
        }
        case 2:
            printAllTours(tourList);
            break;
        case 3: {
            printf("Введите ID тура для поиска: ");
            int searchId;
            scanf_s("%d", &searchId);
            Tour* found = findTourById(tourList, searchId);
            if (found != NULL) {
                printf("\nТур найден:\n");
                printf("ID: %d\n", found->id);
                printf("Название: %s\n", found->name);
                printf("Страна: %s\n", found->country);
                printf("Количество мест: %d\n", found->places);
                printf("Ответственный: %s\n", found->responsible);
            }
            else {
                printf("Тур с ID %d не найден!\n", searchId);
            }
            break;
        }
        case 4: {
            printf("Введите ID тура для удаления: ");
            int removeId;
            scanf_s("%d", &removeId);
            removeTourById(tourList, removeId);
            break;
        }
        case 5:
            printf("Выход из программы...\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте еще раз.\n");
        }
    } while (choice != 5);

    freeTourList(tourList);
    return 0;
}