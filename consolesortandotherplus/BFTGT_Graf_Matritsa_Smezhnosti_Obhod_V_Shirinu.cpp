#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

const int MAX_VERTICES = 20;

struct MatrixGraph {
    int numVertices;
    int** adjMatrix;
    bool* visited;
};

struct Queue {
    int items[MAX_VERTICES];
    int front = -1;
    int rear = -1;

    bool isEmpty() {
        return rear == -1;
    }

    void enqueue(int value) {
        if (rear == MAX_VERTICES - 1) {
            std::cout << "Очередь переполнена\n";
            return;
        }
        if (front == -1) front = 0;
        items[++rear] = value;
    }

    int dequeue() {
        if (isEmpty()) {
            std::cout << "Очередь пуста\n";
            return -1;
        }
        int item = items[front++];
        if (front > rear) front = rear = -1;
        return item;
    }
};

MatrixGraph* createMatrixGraph(int vertices) {
    MatrixGraph* graph = new MatrixGraph;
    graph->numVertices = vertices;

    graph->adjMatrix = new int* [vertices];
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = new int[vertices] {};
    }

    graph->visited = new bool[vertices] {};
    return graph;
}

void addEdge(MatrixGraph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1;
    }
}

void resetVisited(MatrixGraph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = false;
    }
}

void BFS(MatrixGraph* graph, int startVertex) {
    Queue q;
    graph->visited[startVertex] = true;
    q.enqueue(startVertex);

    std::cout << "BFS обход: ";
    while (!q.isEmpty()) {
        int current = q.dequeue();
        std::cout << current << " ";

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[current][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = true;
                q.enqueue(i);
            }
        }
    }
    std::cout << "\n";
}

void BFSComplete(MatrixGraph* graph) {
    resetVisited(graph);
    for (int v = 0; v < graph->numVertices; v++) {
        if (!graph->visited[v]) {
            std::cout << "Компонента связности начиная с вершины " << v << ":\n";
            BFS(graph, v);
        }
    }
}

int BFSShortestPath(MatrixGraph* graph, int start, int end, int* path) {
    resetVisited(graph);
    Queue q;
    int* parent = new int[graph->numVertices];
    int* distance = new int[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
        distance[i] = -1;
    }

    graph->visited[start] = true;
    distance[start] = 0;
    q.enqueue(start);

    while (!q.isEmpty()) {
        int current = q.dequeue();

        if (current == end) {
            int pathLength = 0, temp = end;
            while (temp != -1) {
                path[pathLength++] = temp;
                temp = parent[temp];
            }
            std::reverse(path, path + pathLength);

            delete[] parent;
            delete[] distance;
            return pathLength;
        }

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[current][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = true;
                parent[i] = current;
                distance[i] = distance[current] + 1;
                q.enqueue(i);
            }
        }
    }

    delete[] parent;
    delete[] distance;
    return -1;
}

void findPathsOfLength(MatrixGraph* graph, int start, int length, int* currentPath, int pathIndex, int currentLength) {
    currentPath[pathIndex] = start;

    if (currentLength == length) {
        std::cout << "Путь длины " << length << ": ";
        for (int i = 0; i <= pathIndex; i++) {
            std::cout << currentPath[i];
            if (i < pathIndex) std::cout << " -> ";
        }
        std::cout << "\n";
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[start][i] == 1) {
            bool inPath = false;
            for (int j = 0; j <= pathIndex; j++) {
                if (currentPath[j] == i) {
                    inPath = true;
                    break;
                }
            }
            if (!inPath || currentLength == length - 1)
                findPathsOfLength(graph, i, length, currentPath, pathIndex + 1, currentLength + 1);
        }
    }
}

int getVertexDegree(MatrixGraph* graph, int vertex) {
    int degree = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1) degree++;
    }
    return degree;
}

void printMatrix(MatrixGraph* graph) {
    std::cout << "Матрица смежности:\n   ";
    for (int i = 0; i < graph->numVertices; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < graph->numVertices; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < graph->numVertices; j++) {
            std::cout << graph->adjMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void freeGraph(MatrixGraph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        delete[] graph->adjMatrix[i];
    }
    delete[] graph->adjMatrix;
    delete[] graph->visited;
    delete graph;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    MatrixGraph* graph = createMatrixGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printMatrix(graph);
    BFS(graph, 0);

    int path[MAX_VERTICES];
    int length = BFSShortestPath(graph, 0, 5, path);
    if (length != -1) {
        std::cout << "Кратчайший путь от 0 до 5: ";
        for (int i = 0; i < length; i++) {
            std::cout << path[i];
            if (i < length - 1) std::cout << " -> ";
        }
        std::cout << " (длина: " << length - 1 << ")\n";
    }
    else {
        std::cout << "Путь от 0 до 5 не найден\n";
    }

    std::cout << "\nВсе пути длины 3 от вершины 0:\n";
    int currentPath[MAX_VERTICES];
    findPathsOfLength(graph, 0, 3, currentPath, 0, 0);

    std::cout << "\nГраф с несвязными компонентами:\n";
    MatrixGraph* graph2 = createMatrixGraph(8);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 3, 4);
    addEdge(graph2, 4, 5);
    addEdge(graph2, 6, 7);

    printMatrix(graph2);
    BFSComplete(graph2);

    std::cout << "\nСтепени вершин в первом графе:\n";
    for (int i = 0; i < graph->numVertices; i++) {
        std::cout << "v" << i << "=" << getVertexDegree(graph, i) << " ";
    }
    std::cout << "\n";

    freeGraph(graph);
    freeGraph(graph2);
    return 0;
}
