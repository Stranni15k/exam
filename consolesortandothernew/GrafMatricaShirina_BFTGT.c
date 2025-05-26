/*
 * ГРАФ - МАТРИЦА СМЕЖНОСТИ + ОБХОД В ШИРИНУ (BFS)
 * 
 * Представление графа матрицей смежности:
 * - Двумерный массив размером V×V, где V - количество вершин
 * - adjMatrix[i][j] = 1, если есть ребро между вершинами i и j
 * - adjMatrix[i][j] = 0, если ребра нет
 * - Простая проверка существования ребра O(1)
 * 
 * Обход в ширину (Breadth-First Search):
 * - Обходим все вершины на расстоянии 1, затем 2, затем 3...
 * - Используем очередь (FIFO) для хранения вершин
 * - Помечаем посещенные вершины
 * - Находит кратчайший путь в невзвешенном графе
 * 
 * Сложность:
 * - Время: O(V²) - проверяем всю матрицу
 * - Память: O(V²) для матрицы + O(V) для очереди
 * - Подходит для плотных графов
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Структура графа с матрицей смежности
typedef struct Graph {
    int numVertices;      // Количество вершин
    int** adjMatrix;      // Матрица смежности V×V
    int* visited;         // Массив отметок о посещении вершин
} Graph;

// Очередь для BFS (простая реализация на массиве)
typedef struct Queue {
    int items[100];  // Массив элементов
    int front;       // Индекс первого элемента
    int rear;        // Индекс последнего элемента
} Queue;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    
    graph->visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = 0;
    }
    
    return graph;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) {
        printf("Очередь переполнена\n");
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Очередь пуста\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Обход в ширину (BFS) с матрицей смежности и очередью
void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();  // Создаем очередь
    
    // Помечаем стартовую вершину как посещенную и добавляем в очередь
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    // Обрабатываем вершины пока очередь не пуста
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);  // Извлекаем вершину из очереди
        printf("%d ", currentVertex);    // Выводим текущую вершину
        
        // Проверяем все возможные смежные вершины (весь ряд матрицы)
        for (int i = 0; i < graph->numVertices; i++) {
            // Если есть ребро к вершине i И она не посещена
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = 1;  // Помечаем как посещенную
                enqueue(q, i);          // Добавляем в очередь
            }
        }
    }
}

void printGraph(Graph* graph) {
    printf("Матрица смежности:\n");
    printf("   ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Граф (матрица смежности) с обходом в ширину ===\n");
    
    Graph* graph = createGraph(5);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    
    printGraph(graph);
    
    printf("\nОбход в ширину начиная с вершины 0: ");
    BFS(graph, 0);
    printf("\n");
    
    return 0;
} 