/*
 * ГРАФ - СПИСКИ СМЕЖНОСТИ + ОБХОД В ГЛУБИНУ (DFS)
 * 
 * Представление графа списками смежности:
 * - Для каждой вершины храним список соседних вершин
 * - Экономия памяти для разреженных графов
 * - Быстрое добавление ребер O(1)
 * 
 * Обход в глубину (Depth-First Search):
 * - Идем как можно глубже по одному пути
 * - Используем рекурсию или стек
 * - Помечаем посещенные вершины
 * 
 * Сложность:
 * - Время: O(V + E), где V - вершины, E - ребра
 * - Память: O(V) для разреженных графов
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

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Рекурсивный обход в глубину (DFS)
void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];  // Получаем список смежности
    Node* temp = adjList;
    
    // Помечаем текущую вершину как посещенную
    graph->visited[vertex] = 1;
    printf("%d ", vertex);  // Выводим вершину
    
    // Проходим по всем смежным вершинам
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        
        // Если смежная вершина не посещена - рекурсивно обходим ее
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);  // Рекурсивный вызов
        }
        temp = temp->next;  // Переходим к следующей смежной вершине
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
    
    printf("=== Граф (списки смежности) с обходом в глубину ===\n");
    
    Graph* graph = createGraph(5);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    
    printf("Граф:\n");
    printGraph(graph);
    
    printf("\nОбход в глубину начиная с вершины 0: ");
    DFS(graph, 0);
    printf("\n");
    
    return 0;
} 