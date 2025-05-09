#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct path {
    int tover;
    int weight;
};

struct Queue {
    int inf;
    Queue* next;
};

void push(Queue*& h, Queue*& t, int x) {
    Queue* r = new Queue;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

int pop(Queue*& h, Queue*& t) {
    if (!h) return -1;
    Queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h) t = nullptr;
    delete r;
    return i;
}

vector<vector<path>> create_graph() {
    vector<vector<path>> graph = {
        {{1, 1}, {2, 4}},  // вершина 0: ребро к 1 вес 1, к 2 вес 4 
        {{0, 1}, {2, 2}, {3, 6}}, 
        {{0, 4}, {1, 2}, {3, 3}}, 
        {{1, 6}, {2, 3}} 
    };
    return graph;
}

void print_graph(const vector<vector<path>>& graph) {
    cout << "Список смежности графа:" << endl;
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << ": ";
        for (const path& e : graph[i]) {
            cout << "(" << e.tover << ", " << e.weight << ") ";
        }
        cout << endl;
    }
}

void dijkstra_algor(const vector<vector<path>>& graph, int start) { //алгоритм Дейкстрыс приоритетной очередью
    int n = graph.size();
    vector<int> dist(n, 100000000);
    vector<int> parent(n, -1);
    dist[start] = 0;

    // реализация очереди с приоритетами сначала расстояние, замтем вершина
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (const path& e : graph[u]) {
            int v = e.tover;
            int weight = e.weight;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    // вывод
    cout << "Кратчайшие расстояния от вершины " << start << ":" << endl;
    for (int i = 0; i < n; ++i) {
        if (i == start) continue;
        cout << "До вершины " << i << ": " << dist[i] << ", путь: ";
        if (dist[i] > 100000000) {
            cout << "недостижима" << endl;
            continue;
        }
        // восстановление пути
        vector<int> path;
        for (int v = i; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j];
            if (j != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<path>> graph = create_graph();
    print_graph(graph);

    int start = 0;
    cout << "Начальная вершина: " << start << endl;

    dijkstra_algor(graph, start);
    return 0;
}