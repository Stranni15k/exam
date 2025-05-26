/*
 * ГРАФ - МАТРИЦА СМЕЖНОСТИ + ОБХОД В ГЛУБИНУ (DFS)
 * 
 * Представление графа матрицей смежности:
 * - Двумерный массив размером V×V, где V - количество вершин
 * - adjMatrix[i][j] = 1, если есть ребро между вершинами i и j
 * - adjMatrix[i][j] = 0, если ребра нет
 * - Простая проверка существования ребра O(1)
 * 
 * Обход в глубину (Depth-First Search):
 * - Идем как можно глубже по одному пути
 * - Используем рекурсию
 * - Помечаем посещенные вершины
 * 
 * Сложность:
 * - Время: O(V²) - проверяем всю матрицу
 * - Память: O(V²) для матрицы смежности
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

void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Рекурсивный обход в глубину (DFS) с матрицей смежности
void DFS(Graph* graph, int vertex) {
    // Помечаем текущую вершину как посещенную
    graph->visited[vertex] = 1;
    printf("%d ", vertex);  // Выводим вершину
    
    // Проверяем все возможные вершины (от 0 до numVertices-1)
    for (int i = 0; i < graph->numVertices; i++) {
        // Если есть ребро к вершине i И она не посещена
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFS(graph, i);  // Рекурсивно обходим смежную вершину
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
    
    printf("=== Граф (матрица смежности) с обходом в глубину ===\n");
    
    Graph* graph = createGraph(5);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    
    printGraph(graph);
    
    printf("\nОбход в глубину начиная с вершины 0: ");
    DFS(graph, 0);
    printf("\n");
    
    return 0;
} 