#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Структура ребра графа: куда ведет ребро и какая у него задержка (в миллисекундах)
struct Edge {
    int to;
    int weight;
};

// Класс графа, представленного списком смежности
class Graph {
private:
    vector<string> vertices;          // Список имен вершин
    vector<vector<Edge>> adj;         // Список смежности: для каждой вершины список ребер
    vector<bool> active;              // Флаг активности вершины (удаленные вершины помечаются как неактивные)

    // Найти индекс вершины по названию
    int findIndex(const string& name) const {
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (active[i] && vertices[i] == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    Graph() {}  // Конструктор графа

    // Добавление вершины в граф
    int addVertex(const string& name) {
        if (findIndex(name) >= 0) {
            return findIndex(name);
        }
        vertices.push_back(name);
        adj.emplace_back();
        active.push_back(true);
        return static_cast<int>(vertices.size()) - 1;
    }

    // Удаление вершины и всех инцидентных ребер
    bool removeVertex(const string& name) {
        int index = findIndex(name);
        if (index < 0) {
            return false;
        }
        active[index] = false;
        adj[index].clear();
        for (size_t i = 0; i < adj.size(); ++i) {
            if (!active[i]) continue;
            auto& edges = adj[i];
            edges.erase(remove_if(edges.begin(), edges.end(), [index](const Edge& e) {
                return e.to == index;
            }), edges.end());
        }
        return true;
    }

    // Добавление ребра между вершинами. Для неориентированного графа добавляет обратное ребро.
    bool addEdge(const string& from, const string& to, int weight, bool directed = false) {
        int u = findIndex(from);
        int v = findIndex(to);
        if (u < 0 || v < 0 || weight < 0) {
            return false;
        }
        for (const Edge& edge : adj[u]) {
            if (edge.to == v) {
                return false;
            }
        }
        adj[u].push_back({v, weight});
        if (!directed) {
            adj[v].push_back({u, weight});
        }
        return true;
    }

    // Удаление ребра из графа. Для неориентированного графа удаляет и противоположное ребро.
    bool removeEdge(const string& from, const string& to, bool directed = false) {
        int u = findIndex(from);
        int v = findIndex(to);
        if (u < 0 || v < 0) {
            return false;
        }
        bool removed = false;
        auto& edgesU = adj[u];
        size_t before = edgesU.size();
        edgesU.erase(remove_if(edgesU.begin(), edgesU.end(), [v](const Edge& e) {
            return e.to == v;
        }), edgesU.end());
        removed = removed || (edgesU.size() < before);
        if (!directed) {
            auto& edgesV = adj[v];
            before = edgesV.size();
            edgesV.erase(remove_if(edgesV.begin(), edgesV.end(), [u](const Edge& e) {
                return e.to == u;
            }), edgesV.end());
            removed = removed || (edgesV.size() < before);
        }
        return removed;
    }

    // Поиск вершины по имени
    bool findVertex(const string& name) const {
        return findIndex(name) >= 0;
    }

    // Поиск ребра между двумя вершинами
    bool findEdge(const string& from, const string& to) const {
        int u = findIndex(from);
        int v = findIndex(to);
        if (u < 0 || v < 0) {
            return false;
        }
        for (const Edge& e : adj[u]) {
            if (e.to == v) {
                return true;
            }
        }
        return false;
    }

    // Обход графа в ширину (BFS)
    void printBFS(const string& startName) const {
        int start = findIndex(startName);
        if (start < 0) {
            cout << "BFS: вершина не найдена: " << startName << endl;
            return;
        }
        vector<bool> visited(vertices.size(), false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS от " << startName << ": ";
        bool first = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (!active[u]) continue;
            if (!first) cout << ", ";
            cout << vertices[u];
            first = false;
            for (const Edge& e : adj[u]) {
                if (!visited[e.to] && active[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        cout << endl;
    }

    // Обход графа в глубину (DFS)
    void printDFS(const string& startName) const {
        int start = findIndex(startName);
        if (start < 0) {
            cout << "DFS: вершина не найдена: " << startName << endl;
            return;
        }
        vector<bool> visited(vertices.size(), false);
        cout << "DFS от " << startName << ": ";
        dfsVisit(start, visited);
        cout << endl;
    }

    // Рекурсивная часть DFS
    void dfsVisit(int u, vector<bool>& visited) const {
        if (visited[u] || !active[u]) {
            return;
        }
        visited[u] = true;
        cout << vertices[u] << ", ";
        for (const Edge& e : adj[u]) {
            if (!visited[e.to] && active[e.to]) {
                dfsVisit(e.to, visited);
            }
        }
    }

    // Печать списка смежности графа
    void printAdjacencyList() const {
        cout << "\nСписок смежности графа:\n";
        for (size_t u = 0; u < vertices.size(); ++u) {
            if (!active[u]) continue;
            cout << vertices[u] << ": ";
            for (const Edge& e : adj[u]) {
                if (!active[e.to]) continue;
                cout << "(" << vertices[e.to] << ", " << e.weight << " ms) ";
            }
            cout << endl;
        }
    }

    // Нахождение кратчайшего пути между двумя узлами по суммарной задержке
    bool shortestPath(const string& from, const string& to, vector<int>& path, int& totalWeight) const {
        int start = findIndex(from);
        int target = findIndex(to);
        if (start < 0 || target < 0) {
            return false;
        }
        int n = static_cast<int>(vertices.size());
        vector<int> dist(n, numeric_limits<int>::max());
        vector<bool> used(n, false);
        vector<int> prev(n, -1);
        dist[start] = 0;
        for (int i = 0; i < n; ++i) {
            int u = -1;
            int best = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (active[j] && !used[j] && dist[j] < best) {
                    best = dist[j];
                    u = j;
                }
            }
            if (u == -1) break;
            used[u] = true;
            for (const Edge& e : adj[u]) {
                if (!active[e.to]) continue;
                int alt = dist[u] + e.weight;
                if (alt < dist[e.to]) {
                    dist[e.to] = alt;
                    prev[e.to] = u;
                }
            }
        }
        if (dist[target] == numeric_limits<int>::max()) {
            return false;
        }
        totalWeight = dist[target];
        path.clear();
        for (int v = target; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return true;
    }
};

// Отдельная функция для вывода упрощенной схемы сети с указанием задержек
void printNetworkScheme() {
    cout << "\nСхема офисной сети с задержками (ms):\n";
    cout << "Router-A --10-- PC-1\n";
    cout << " |\\\n";
    cout << " 12  15\n";
    cout << " |   \\ \n";
    cout << "PC-2   PC-3\n";
    cout << "\nСоединения между маршрутизаторами:\n";
    cout << "Router-A -- 8 -- Router-B -- 7 -- Router-C -- 9 -- Router-D\n";
    cout << "Router-A --14-- Router-D\n";
    cout << "Дополнительные компьютеры:\n";
    cout << "Router-B: PC-4 (11), PC-5 (13), PC-6 (16)\n";
    cout << "Router-C: PC-7 (10), PC-8 (12), PC-9 (14)\n";
    cout << "Router-D: PC-10 (9), PC-11 (10), PC-12 (10), PC-13 (11), PC-14 (12), PC-15 (14), PC-16 (15)\n";
}

int main() {
    // Создание графа компьютерной сети и заполнение вершин
    Graph graph;

    vector<string> nodes = {
        "Router-A", "Router-B", "Router-C", "Router-D",
        "PC-1", "PC-2", "PC-3", "PC-4", "PC-5", "PC-6",
        "PC-7", "PC-8", "PC-9", "PC-10", "PC-11", "PC-12",
        "PC-13", "PC-14", "PC-15", "PC-16"
    };

    for (const auto& node : nodes) {
        graph.addVertex(node);
    }

    graph.addEdge("Router-A", "PC-1", 10);
    graph.addEdge("Router-A", "PC-2", 12);
    graph.addEdge("Router-A", "PC-3", 15);
    graph.addEdge("Router-A", "Router-B", 8);
    graph.addEdge("Router-B", "PC-4", 11);
    graph.addEdge("Router-B", "PC-5", 13);
    graph.addEdge("Router-B", "PC-6", 16);
    graph.addEdge("Router-B", "Router-C", 7);
    graph.addEdge("Router-C", "PC-7", 10);
    graph.addEdge("Router-C", "PC-8", 12);
    graph.addEdge("Router-C", "PC-9", 14);
    graph.addEdge("Router-C", "Router-D", 9);
    graph.addEdge("Router-D", "PC-10", 9);
    graph.addEdge("Router-D", "PC-11", 10);
    graph.addEdge("Router-D", "PC-12", 10);
    graph.addEdge("Router-D", "PC-13", 11);
    graph.addEdge("Router-D", "PC-14", 12);
    graph.addEdge("Router-D", "PC-15", 14);
    graph.addEdge("Router-D", "PC-16", 15);
    graph.addEdge("Router-A", "Router-D", 14);

    printNetworkScheme();
    graph.printAdjacencyList();

    cout << "\nПроверка поиска вершин и ребер:\n";
    cout << "Найдена ли вершина 'PC-7': " << (graph.findVertex("PC-7") ? "Да" : "Нет") << endl;
    cout << "Найдено ли ребро 'Router-A' -> 'Router-B': " << (graph.findEdge("Router-A", "Router-B") ? "Да" : "Нет") << endl;
    cout << "Найдено ли ребро 'PC-1' -> 'PC-4': " << (graph.findEdge("PC-1", "PC-4") ? "Да" : "Нет") << endl;

    cout << "\nОбходы графа:\n";
    graph.printBFS("Router-A");
    graph.printDFS("Router-A");

    cout << "\nКратчайший путь по задержке между 'PC-1' и 'PC-14':\n";
    vector<int> path;
    int totalDelay = 0;
    if (graph.shortestPath("PC-1", "PC-14", path, totalDelay)) {
        cout << "Путь: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << " -> ";
            cout << (path[i] >= 0 ? nodes[path[i]] : string("?"));
        }
        cout << endl;
        cout << "Общая задержка: " << totalDelay << " ms" << endl;
    } else {
        cout << "Путь не найден." << endl;
    }

    cout << "\nУдаление ребра Router-A <-> Router-D и повторный обход BFS:\n";
    graph.removeEdge("Router-A", "Router-D");
    graph.printBFS("Router-A");

    cout << "\nУдаление вершины PC-3 и вывод списка смежности после удаления:\n";
    graph.removeVertex("PC-3");
    graph.printAdjacencyList();

    return 0;
}
