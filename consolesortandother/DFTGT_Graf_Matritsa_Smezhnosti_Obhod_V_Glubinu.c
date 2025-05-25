 
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_VERTICES 20

struct MatrixGraph {
    int numVertices;
    int** adjMatrix;
    int* visited;
};

typedef struct MatrixGraph MatrixGraph;

 
MatrixGraph* createMatrixGraph(int vertices) {
    MatrixGraph* graph = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    graph->numVertices = vertices;
    
     
    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    
    graph->visited = (int*)calloc(vertices, sizeof(int));
    
    return graph;
}

 
void addEdgeMatrix(MatrixGraph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1;  
    }
}

 
void removeEdgeMatrix(MatrixGraph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 0;
        graph->adjMatrix[dest][src] = 0;
    }
}

 
void DFSMatrix(MatrixGraph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFSMatrix(graph, i);
        }
    }
}

 
void resetVisitedMatrix(MatrixGraph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

 
void printMatrixGraph(MatrixGraph* graph) {
    printf("Матрица смежности:\n");
    printf("   ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%2d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

 
void DFSCompleteMatrix(MatrixGraph* graph) {
    resetVisitedMatrix(graph);
    printf("DFS обход: ");
    
    for (int v = 0; v < graph->numVertices; v++) {
        if (!graph->visited[v]) {
            printf("[Компонента: ");
            DFSMatrix(graph, v);
            printf("] ");
        }
    }
    printf("\n");
}

 
int DFSPathMatrix(MatrixGraph* graph, int start, int end, int* path, int pathIndex) {
    graph->visited[start] = 1;
    path[pathIndex] = start;
    
    if (start == end) {
        return pathIndex + 1;  
    }
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[start][i] == 1 && !graph->visited[i]) {
            int result = DFSPathMatrix(graph, i, end, path, pathIndex + 1);
            if (result != -1) {
                return result;  
            }
        }
    }
    
    return -1;  
}

 
int isConnected(MatrixGraph* graph) {
    resetVisitedMatrix(graph);
    DFSMatrix(graph, 0);
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            return 0;  
        }
    }
    return 1;  
}

 
int getVertexDegree(MatrixGraph* graph, int vertex) {
    int degree = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1) {
            degree++;
        }
    }
    return degree;
}

 
void printGraphInfo(MatrixGraph* graph) {
    printf("\nИнформация о графе:\n");
    printf("Количество вершин: %d\n", graph->numVertices);
    
    int totalEdges = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = i + 1; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                totalEdges++;
            }
        }
    }
    printf("Количество рёбер: %d\n", totalEdges);
    
    printf("Степени вершин: ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("v%d=%d ", i, getVertexDegree(graph, i));
    }
    printf("\n");
    
    printf("Граф %s\n", isConnected(graph) ? "связный" : "не связный");
}

 
void freeMatrixGraph(MatrixGraph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph->visited);
    free(graph);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("=== Демонстрация графа (матрица смежности) с DFS ===\n");
    
     
    MatrixGraph* graph = createMatrixGraph(6);
    
     
    addEdgeMatrix(graph, 0, 1);
    addEdgeMatrix(graph, 0, 2);
    addEdgeMatrix(graph, 1, 3);
    addEdgeMatrix(graph, 2, 4);
    addEdgeMatrix(graph, 3, 4);
    addEdgeMatrix(graph, 4, 5);
    
     
    printMatrixGraph(graph);
    printGraphInfo(graph);
    
     
    DFSCompleteMatrix(graph);
    
     
    resetVisitedMatrix(graph);
    int path[MAX_VERTICES];
    int pathLength = DFSPathMatrix(graph, 0, 5, path, 0);
    
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
    
     
    printf("\nУдаляем ребро 3-4:\n");
    removeEdgeMatrix(graph, 3, 4);
    printMatrixGraph(graph);
    printGraphInfo(graph);
    
     
    printf("\nГраф с несвязными компонентами:\n");
    MatrixGraph* graph2 = createMatrixGraph(7);
    addEdgeMatrix(graph2, 0, 1);
    addEdgeMatrix(graph2, 1, 2);
    addEdgeMatrix(graph2, 3, 4);
    addEdgeMatrix(graph2, 5, 6);
    
    printMatrixGraph(graph2);
    printGraphInfo(graph2);
    DFSCompleteMatrix(graph2);
    
     
    freeMatrixGraph(graph);
    freeMatrixGraph(graph2);
    
    return 0;
} 
