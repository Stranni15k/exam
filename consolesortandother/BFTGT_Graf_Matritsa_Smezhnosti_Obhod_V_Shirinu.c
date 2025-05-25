 
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

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

typedef struct MatrixGraph MatrixGraph;
typedef struct Queue Queue;

 
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
    if (q->rear == MAX_VERTICES - 1) {
        printf("Очередь переполнена\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Очередь пуста\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

 
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

 
void BFSMatrix(MatrixGraph* graph, int startVertex) {
    Queue* q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    printf("BFS обход: ");
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
    free(q);
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

 
void BFSCompleteMatrix(MatrixGraph* graph) {
    resetVisitedMatrix(graph);
    
    for (int v = 0; v < graph->numVertices; v++) {
        if (!graph->visited[v]) {
            printf("Компонента связности начиная с вершины %d:\n", v);
            BFSMatrix(graph, v);
        }
    }
}

 
int BFSShortestPathMatrix(MatrixGraph* graph, int start, int end, int* path) {
    resetVisitedMatrix(graph);
    Queue* q = createQueue();
    int* parent = (int*)malloc(graph->numVertices * sizeof(int));
    int* distance = (int*)malloc(graph->numVertices * sizeof(int));
    
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
        distance[i] = -1;
    }
    
    graph->visited[start] = 1;
    distance[start] = 0;
    enqueue(q, start);
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        
        if (currentVertex == end) {
             
            int pathLength = 0;
            int temp = end;
            while (temp != -1) {
                path[pathLength++] = temp;
                temp = parent[temp];
            }
            
             
            for (int i = 0; i < pathLength / 2; i++) {
                int tempVal = path[i];
                path[i] = path[pathLength - 1 - i];
                path[pathLength - 1 - i] = tempVal;
            }
            
            int finalDistance = distance[end];
            free(q);
            free(parent);
            free(distance);
            return pathLength;
        }
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = 1;
                parent[i] = currentVertex;
                distance[i] = distance[currentVertex] + 1;
                enqueue(q, i);
            }
        }
    }
    
    free(q);
    free(parent);
    free(distance);
    return -1;  
}

 
void findPathsOfLength(MatrixGraph* graph, int start, int length, int* currentPath, int pathIndex, int currentLength) {
    currentPath[pathIndex] = start;
    
    if (currentLength == length) {
        printf("Путь длины %d: ", length);
        for (int i = 0; i <= pathIndex; i++) {
            printf("%d", currentPath[i]);
            if (i < pathIndex) printf(" -> ");
        }
        printf("\n");
        return;
    }
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[start][i] == 1) {
             
            int inPath = 0;
            for (int j = 0; j <= pathIndex; j++) {
                if (currentPath[j] == i) {
                    inPath = 1;
                    break;
                }
            }
            
            if (!inPath || currentLength == length - 1) {
                findPathsOfLength(graph, i, length, currentPath, pathIndex + 1, currentLength + 1);
            }
        }
    }
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

    printf("=== Демонстрация графа (матрица смежности) с BFS ===\n");
    
     
    MatrixGraph* graph = createMatrixGraph(6);
    
     
    addEdgeMatrix(graph, 0, 1);
    addEdgeMatrix(graph, 0, 2);
    addEdgeMatrix(graph, 1, 3);
    addEdgeMatrix(graph, 2, 4);
    addEdgeMatrix(graph, 3, 4);
    addEdgeMatrix(graph, 4, 5);
    
     
    printMatrixGraph(graph);
    printf("\n");
    
     
    BFSMatrix(graph, 0);
    
     
    resetVisitedMatrix(graph);
    int path[MAX_VERTICES];
    int pathLength = BFSShortestPathMatrix(graph, 0, 5, path);
    
    if (pathLength != -1) {
        printf("Кратчайший путь от 0 до 5: ");
        for (int i = 0; i < pathLength; i++) {
            printf("%d", path[i]);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf(" (длина: %d)\n", pathLength - 1);
    } else {
        printf("Путь от 0 до 5 не найден\n");
    }
    
     
    printf("\nВсе пути длины 3 от вершины 0:\n");
    int currentPath[MAX_VERTICES];
    findPathsOfLength(graph, 0, 3, currentPath, 0, 0);
    
     
    printf("\nГраф с несвязными компонентами:\n");
    MatrixGraph* graph2 = createMatrixGraph(8);
    addEdgeMatrix(graph2, 0, 1);
    addEdgeMatrix(graph2, 1, 2);
    addEdgeMatrix(graph2, 3, 4);
    addEdgeMatrix(graph2, 4, 5);
    addEdgeMatrix(graph2, 6, 7);
    
    printMatrixGraph(graph2);
    BFSCompleteMatrix(graph2);
    
     
    printf("\nСтепени вершин в первом графе: ");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("v%d=%d ", i, getVertexDegree(graph, i));
    }
    printf("\n");
    
     
    freeMatrixGraph(graph);
    freeMatrixGraph(graph2);
    
    return 0;
} 
