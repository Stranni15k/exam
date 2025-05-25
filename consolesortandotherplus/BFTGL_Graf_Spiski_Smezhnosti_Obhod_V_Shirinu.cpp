#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

const int MAX_VERTICES = 20;

struct AdjListNode {
    int dest;
    AdjListNode* next;
};

struct AdjList {
    AdjListNode* head;
};

struct Graph {
    int numVertices;
    AdjList* array;
    int* visited;
};

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        std::cout << "Очередь переполнена\n";
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        std::cout << "Очередь пуста\n";
        return -1;
    }
    int item = q->items[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}

AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = nullptr;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = new Graph;
    graph->numVertices = vertices;
    graph->array = new AdjList[vertices];
    graph->visited = new int[vertices] {0};

    for (int i = 0; i < vertices; ++i) {
        graph->array[i].head = nullptr;
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

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        graph->visited[i] = 0;
    }
}

void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    std::cout << "BFS обход: ";

    while (!isEmpty(q)) {
        int current = dequeue(q);
        std::cout << current << " ";

        AdjListNode* temp = graph->array[current].head;
        while (temp) {
            int adj = temp->dest;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                enqueue(q, adj);
            }
            temp = temp->next;
        }
    }

    std::cout << "\n";
    delete q;
}

void BFSComplete(Graph* graph) {
    resetVisited(graph);
    for (int v = 0; v < graph->numVertices; ++v) {
        if (!graph->visited[v]) {
            std::cout << "Компонента связности начиная с вершины " << v << ":\n";
            BFS(graph, v);
        }
    }
}

int BFSShortestPath(Graph* graph, int start, int end, int* path) {
    resetVisited(graph);
    Queue* q = createQueue();
    int* parent = new int[graph->numVertices];
    for (int i = 0; i < graph->numVertices; ++i) parent[i] = -1;

    graph->visited[start] = 1;
    enqueue(q, start);

    while (!isEmpty(q)) {
        int current = dequeue(q);
        if (current == end) {
            int len = 0, temp = end;
            while (temp != -1) {
                path[len++] = temp;
                temp = parent[temp];
            }
            for (int i = 0; i < len / 2; ++i) {
                std::swap(path[i], path[len - i - 1]);
            }

            delete[] parent;
            delete q;
            return len;
        }

        AdjListNode* temp = graph->array[current].head;
        while (temp) {
            int adj = temp->dest;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                parent[adj] = current;
                enqueue(q, adj);
            }
            temp = temp->next;
        }
    }

    delete[] parent;
    delete q;
    return -1;
}

void printGraph(Graph* graph) {
    std::cout << "Граф (списки смежности):\n";
    for (int v = 0; v < graph->numVertices; ++v) {
        std::cout << "Вершина " << v << ": ";
        AdjListNode* temp = graph->array[v].head;
        while (temp) {
            std::cout << temp->dest << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}

void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        AdjListNode* current = graph->array[v].head;
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] graph->array;
    delete[] graph->visited;
    delete graph;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printGraph(graph);
    BFS(graph, 0);

    int path[MAX_VERTICES];
    int len = BFSShortestPath(graph, 0, 5, path);
    if (len != -1) {
        std::cout << "Кратчайший путь от 0 до 5: ";
        for (int i = 0; i < len; ++i) {
            std::cout << path[i];
            if (i < len - 1) std::cout << " -> ";
        }
        std::cout << " (длина: " << len - 1 << ")\n";
    }
    else {
        std::cout << "Путь от 0 до 5 не найден\n";
    }

    std::cout << "\nГраф с несвязными компонентами:\n";
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
