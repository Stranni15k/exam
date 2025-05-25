 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_VERTICES 20

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int numVertices;
    struct AdjList* array;
    int* visited;
};

typedef struct AdjListNode AdjListNode;
typedef struct AdjList AdjList;
typedef struct Graph Graph;

 
AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

 
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));
    graph->visited = (int*)calloc(vertices, sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

 
void addEdge(Graph* graph, int src, int dest) {
     
    AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
     
    newNode = createAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

 
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    
    AdjListNode* current = graph->array[vertex].head;
    while (current != NULL) {
        int adjVertex = current->dest;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        current = current->next;
    }
}

 
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

 
void printGraph(Graph* graph) {
    printf("Граф (списки смежности):\n");
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* current = graph->array[v].head;
        printf("Вершина %d: ", v);
        while (current) {
            printf("%d ", current->dest);
            current = current->next;
        }
        printf("\n");
    }
}

 
void DFSComplete(Graph* graph) {
    resetVisited(graph);
    printf("DFS обход: ");
    
    for (int v = 0; v < graph->numVertices; v++) {
        if (!graph->visited[v]) {
            printf("[Компонента: ");
            DFS(graph, v);
            printf("] ");
        }
    }
    printf("\n");
}

 
int DFSPath(Graph* graph, int start, int end, int* path, int pathIndex) {
    graph->visited[start] = 1;
    path[pathIndex] = start;
    
    if (start == end) {
        return pathIndex + 1;  
    }
    
    AdjListNode* current = graph->array[start].head;
    while (current != NULL) {
        int adjVertex = current->dest;
        if (!graph->visited[adjVertex]) {
            int result = DFSPath(graph, adjVertex, end, path, pathIndex + 1);
            if (result != -1) {
                return result;  
            }
        }
        current = current->next;
    }
    
    return -1;  
}

 
void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* current = graph->array[v].head;
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph->visited);
    free(graph);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация графа (списки смежности) с DFS ===\n");
    
     
    Graph* graph = createGraph(6);
    
     
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    
     
    printGraph(graph);
    printf("\n");
    
     
    DFSComplete(graph);
    
     
    resetVisited(graph);
    int path[MAX_VERTICES];
    int pathLength = DFSPath(graph, 0, 5, path, 0);
    
    if (pathLength != -1) {
        printf("Путь от 0 до 5: ");
        for (int i = 0; i < pathLength; i++) {
            printf("%d", path[i]);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("Путь от 0 до 5 не найден\n");
    }
    
     
    printf("\nГраф с несвязными компонентами:\n");
    Graph* graph2 = createGraph(7);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 3, 4);
    addEdge(graph2, 5, 6);
    
    printGraph(graph2);
    DFSComplete(graph2);
    
     
    freeGraph(graph);
    freeGraph(graph2);
    
    return 0;
} 
