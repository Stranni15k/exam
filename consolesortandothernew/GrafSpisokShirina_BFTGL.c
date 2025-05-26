/*
 * ГРАФ - СПИСКИ СМЕЖНОСТИ + ОБХОД В ШИРИНУ (BFS)
 * 
 * Представление графа списками смежности:
 * - Для каждой вершины храним список соседних вершин
 * - Экономия памяти для разреженных графов
 * - Быстрое добавление ребер O(1)
 * 
 * Обход в ширину (Breadth-First Search):
 * - Обходим все вершины на расстоянии 1, затем 2, затем 3...
 * - Используем очередь (FIFO) для хранения вершин
 * - Помечаем посещенные вершины
 * - Находит кратчайший путь в невзвешенном графе
 * 
 * Сложность:
 * - Время: O(V + E), где V - вершины, E - ребра
 * - Память: O(V) для очереди и массива visited
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

// Узел в списке смежности
typedef struct Node {
    int vertex;           // Номер смежной вершины
    struct Node* next;    // Указатель на следующую смежную вершину
} Node;

// Структура графа
typedef struct Graph {
    int numVertices;      // Количество вершин
    Node** adjLists;      // Массив списков смежности
    int* visited;         // Массив отметок о посещении вершин
} Graph;

// Очередь для BFS (простая реализация на массиве)
typedef struct Queue {
    int items[100];  // Массив элементов
    int front;       // Индекс первого элемента
    int rear;        // Индекс последнего элемента
} Queue;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
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
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Обход в ширину (BFS) с использованием очереди
void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();  // Создаем очередь
    
    // Помечаем стартовую вершину как посещенную и добавляем в очередь
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    // Обрабатываем вершины пока очередь не пуста
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);  // Извлекаем вершину из очереди
        printf("%d ", currentVertex);    // Выводим текущую вершину
        
        // Проходим по всем смежным вершинам
        Node* temp = graph->adjLists[currentVertex];
        
        while (temp) {
            int adjVertex = temp->vertex;
            
            // Если смежная вершина не посещена - добавляем в очередь
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;  // Помечаем как посещенную
                enqueue(q, adjVertex);          // Добавляем в очередь
            }
            temp = temp->next;  // Переходим к следующей смежной вершине
        }
    }
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Вершина %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    SetConsoleCP(1251); // либо CP_UTF8
    SetConsoleOutputCP(1251);
    
    printf("=== Граф (списки смежности) с обходом в ширину ===\n");
    
    Graph* graph = createGraph(5);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    
    printf("Граф:\n");
    printGraph(graph);
    
    printf("\nОбход в ширину начиная с вершины 0: ");
    BFS(graph, 0);
    printf("\n");
    
    return 0;
} 