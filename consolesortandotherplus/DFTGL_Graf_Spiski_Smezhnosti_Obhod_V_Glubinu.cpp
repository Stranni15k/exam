#include <iostream>
#include <vector>
#include <list>

#ifdef _WIN32
#include <windows.h>
#endif

class Graph {
private:
    int numVertices;
    std::vector<std::list<int>> adjList;
    std::vector<bool> visited;

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
        visited.resize(vertices, false);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // для неориентированного графа
    }

    void resetVisited() {
        std::fill(visited.begin(), visited.end(), false);
    }

    void DFS(int vertex) {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int adj : adjList[vertex]) {
            if (!visited[adj]) {
                DFS(adj);
            }
        }
    }

    void DFSComplete() {
        resetVisited();
        std::cout << "DFS обход: ";
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v]) {
                std::cout << "[Компонента: ";
                DFS(v);
                std::cout << "] ";
            }
        }
        std::cout << "\n";
    }

    bool DFSPath(int start, int end, std::vector<int>& path) {
        visited[start] = true;
        path.push_back(start);

        if (start == end) return true;

        for (int adj : adjList[start]) {
            if (!visited[adj]) {
                if (DFSPath(adj, end, path)) return true;
            }
        }

        path.pop_back();
        return false;
    }

    void printGraph() {
        std::cout << "Граф (списки смежности):\n";
        for (int v = 0; v < numVertices; ++v) {
            std::cout << "Вершина " << v << ": ";
            for (int adj : adjList[v]) {
                std::cout << adj << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::cout << "=== Демонстрация графа (списки смежности) с DFS ===\n";

    Graph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);

    graph.printGraph();
    std::cout << "\n";
    graph.DFSComplete();

    graph.resetVisited();
    std::vector<int> path;
    if (graph.DFSPath(0, 5, path)) {
        std::cout << "Путь от 0 до 5: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Путь от 0 до 5 не найден\n";
    }

    std::cout << "\nГраф с несвязными компонентами:\n";
    Graph graph2(7);
    graph2.addEdge(0, 1);
    graph2.addEdge(1, 2);
    graph2.addEdge(3, 4);
    graph2.addEdge(5, 6);
    graph2.printGraph();
    graph2.DFSComplete();

    return 0;
}
