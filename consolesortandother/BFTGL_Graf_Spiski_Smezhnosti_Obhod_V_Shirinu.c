 
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

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

typedef struct AdjListNode AdjListNode;
typedef struct AdjList AdjList;
typedef struct Graph Graph;
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

 
void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    printf("BFS обход: ");
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        AdjListNode* current = graph->array[currentVertex].head;
        
        while (current) {
            int adjVertex = current->dest;
            
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            current = current->next;
        }
    }
    printf("\n");
    free(q);
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

 
void BFSComplete(Graph* graph) {
    resetVisited(graph);
    
    for (int v = 0; v < graph->numVertices; v++) {
        if (!graph->visited[v]) {
            printf("Компонента связности начиная с вершины %d:\n", v);
            BFS(graph, v);
        }
    }
}

 
int BFSShortestPath(Graph* graph, int start, int end, int* path) {
    resetVisited(graph);
    Queue* q = createQueue();
    int* parent = (int*)malloc(graph->numVertices * sizeof(int));
    
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
    }
    
    graph->visited[start] = 1;
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
            
            free(q);
            free(parent);
            return pathLength;
        }
        
        AdjListNode* current = graph->array[currentVertex].head;
        while (current) {
            int adjVertex = current->dest;
            
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                parent[adjVertex] = currentVertex;
                enqueue(q, adjVertex);
            }
            current = current->next;
        }
    }
    
    free(q);
    free(parent);
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

    printf("=== Демонстрация графа (списки смежности) с BFS ===\n");
    
     
    Graph* graph = createGraph(6);
    
     
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    
     
    printGraph(graph);
    printf("\n");
    
     
    BFS(graph, 0);
    
     
    resetVisited(graph);
    int path[MAX_VERTICES];
    int pathLength = BFSShortestPath(graph, 0, 5, path);
    
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
    
     
    printf("\nГраф с несвязными компонентами:\n");
    Graph* graph2 = createGraph(8);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 3, 4);
    addEdge(graph2, 4, 5);
    addEdge(graph2, 6, 7);
    
    printGraph(graph2);
    BFSComplete(graph2);
    
     
    freeGraph(graph);
    freeGraph(graph2);
    
    return 0;
} 
