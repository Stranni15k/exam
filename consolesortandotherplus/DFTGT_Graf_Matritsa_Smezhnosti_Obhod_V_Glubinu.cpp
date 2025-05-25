#include <iostream>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<bool> visited;

public:
    Graph(int vertices) : numVertices(vertices), adjMatrix(vertices, std::vector<int>(vertices, 0)), visited(vertices, false) {}

    void addEdge(int src, int dest) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjMatrix[src][dest] = 1;
            adjMatrix[dest][src] = 1; // Для неориентированного графа
        }
    }

    void removeEdge(int src, int dest) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjMatrix[src][dest] = 0;
            adjMatrix[dest][src] = 0;
        }
    }

    void DFS(int vertex) {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                DFS(i);
            }
        }
    }

    void DFSComplete() {
        std::fill(visited.begin(), visited.end(), false);
        std::cout << "DFS обход: ";

        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v]) {
                std::cout << "[Компонента: ";
                DFS(v);
                std::cout << "] ";
            }
        }
        std::cout << std::endl;
    }

    void printMatrix() const {
        std::cout << "Матрица смежности:\n    ";
        for (int i = 0; i < numVertices; ++i)
            std::cout << std::setw(2) << i << " ";
        std::cout << "\n";

        for (int i = 0; i < numVertices; ++i) {
            std::cout << std::setw(2) << i << " ";
            for (int j = 0; j < numVertices; ++j) {
                std::cout << std::setw(2) << adjMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    int getVertexDegree(int vertex) const {
        int degree = 0;
        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[vertex][i] == 1) {
                degree++;
            }
        }
        return degree;
    }

    void printGraphInfo() {
        std::cout << "\nИнформация о графе:\n";
        std::cout << "Количество вершин: " << numVertices << "\n";

        int totalEdges = 0;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (adjMatrix[i][j] == 1) {
                    totalEdges++;
                }
            }
        }
        std::cout << "Количество рёбер: " << totalEdges << "\n";

        std::cout << "Степени вершин: ";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "v" << i << "=" << getVertexDegree(i) << " ";
        }
        std::cout << "\n";

        std::cout << "Граф " << (isConnected() ? "связный" : "не связный") << "\n";
    }

    bool isConnected() {
        std::fill(visited.begin(), visited.end(), false);
        DFS(0);

        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
};

int main() {
#ifdef _WIN32
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
#endif
    std::cout << "=== Демонстрация графа (матрица смежности) с DFS ===\n";

    Graph graph(6);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);

    graph.printMatrix();
    graph.printGraphInfo();

    graph.DFSComplete();

    std::cout << "\nУдаляем ребро 3-4:\n";
    graph.removeEdge(3, 4);
    graph.printMatrix();
    graph.printGraphInfo();

    return 0;
}
