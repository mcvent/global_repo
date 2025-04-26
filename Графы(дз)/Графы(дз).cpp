//Дан ориентированный граф. Вывести все истоки графа.
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct queue {
    int inf;
    queue* next;
};
void push(queue*& h, queue*& t, int x) {
    queue* r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}
int pop(queue*& h, queue*& t) {
    queue* r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

vector<vector<int>> create_smej_list() {
    int n, m; bool is_orientiring;
    cout << "Введите количество вершин: ";
    cin >> n;
    cout << "Введите количество ребер: ";
    cin >> m;
    cout << "Граф ориентированный (1/0): ";
    cin >> is_orientiring;
    vector<vector<int>> gr;
    gr.resize(n);

    cout << "Введите смежные вершины по 2 штуки" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        if (is_orientiring) {
            if (x >= n || y >= n) {
                cout << "ошибка ввода" << " " << x << " " << y << endl;
                continue;
            }
            gr[x].push_back(y);
        }
        else {
            if (x >= n || y >= n) {
                cout << "error" << x << " " << y << endl;
                continue;
            }
            gr[x].push_back(y);
            gr[y].push_back(x);
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(gr[i].begin(), gr[i].end());
        gr[i].erase(unique(gr[i].begin(), gr[i].end()), gr[i].end());
    }
    return gr;
}

void print_smej_list(vector<vector<int>>& gr) {
    cout << "Вывод cписка смежностей:" << endl;
    for (int i = 0; i < gr.size(); ++i) {
        cout << i << ": ";
        for (int v : gr[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int cin_ver(vector<vector<int>>& gr, int ver) {
    if (ver < 0 || ver >= gr.size()) {
        return -1; // Некорректный номер вершины
    }
    return gr[ver].size();
}

void add_reb(vector<vector<int>>& gr, int a, int b) {
    if (a < 0 || b < 0 || a >= gr.size() || b >= gr.size()) {
        cout << "Вершины не содержатся в графе" << endl;
        return;
    }
    gr[a].push_back(b); // добавляем ребро a--b

    sort(gr[a].begin(), gr[a].end()); // сортировка графа
}

void print_step(vector<vector<int>>& gr) {
    for (int i = 0; i < gr.size(); ++i) {
        cout << "Вершина " << i << ": степень " << gr[i].size() << endl; //поскольку граф неориентированный просто выводим размер списка смежностей
    }
}

void dfs(int v, vector<vector<int>>& gr, vector<bool>& visited) {
    visited[v] = true;
    for (int x : gr[v]) {
        if (!visited[x]) {
            dfs(x, gr, visited);
        }
    }
}

void print_unreach(vector<vector<int>>& gr, int x) {
    if (x < 0 || x >= gr.size()) {
        cout << "вершина не существует" << endl;
        return;
    }

    vector<bool> visited(gr.size(), false); // вектор с посещенным вершинами
    dfs(x, gr, visited);

    cout << "недостижимые вершины: ";
    bool unreachable_ver = false;
    for (int i = 0; i < gr.size(); ++i) {
        if (!visited[i]) {
            cout << i << " ";
            unreachable_ver = true;
        }
    } if (!unreachable_ver) {
        cout << "нет недостижимых вершин";
    }
    cout << endl;
}
struct stack {
    int inf;
    stack* next;
};

void push_s(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_s(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

void dfs_order(int v, const vector<vector<int>>& gr, vector<bool>& visited, stack*& order) {
    visited[v] = true;
    for (int u : gr[v]) {
        if (!visited[u]) {
            dfs_order(u, gr, visited, order);
        }
    }
    push_s(order, v);
}

void bfs_scc(int v, const vector<vector<int>>& gr_t, vector<bool>& visited, vector<int>& component) {
    queue* q_head = nullptr; queue* q_tail = nullptr;
    push(q_head, q_tail, v);
    visited[v] = true;
    component.push_back(v);

    while (q_head != nullptr) {
        int current = pop(q_head, q_tail);
        for (int u : gr_t[current]) {
            if (!visited[u]) {
                visited[u] = true;
                component.push_back(u);
                push(q_head, q_tail, u);
            }
        }
    }
}

vector<vector<int>> find_scc(const vector<vector<int>>& gr) {
    int n = gr.size();
    vector<bool> visited(n, false);
    stack* order = nullptr;

    for (int i = 0; i < n; ++i) { //проходим первый раз для определения порядка прохода
        if (!visited[i]) {
            dfs_order(i, gr, visited, order);
        }
    }
    vector<vector<int>> gr_t(n);
    for (int i = 0; i < n; ++i) { //транспонируем граф, т.е. меняем местами вершины
        for (int j : gr[i]) {
            gr_t[j].push_back(i);
        }
    }
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;
    while (order != nullptr) { //второй проход BFS в порядке посещения вершин
        int v = pop_s(order);
        if (!visited[v]) {
            vector<int> component;
            bfs_scc(v, gr_t, visited, component);
            scc.push_back(component);
        }
    }

    return scc;
}

void print_scc(const vector<vector<int>>& scc) {
    for (int i = 0; i < scc.size(); ++i) {
        cout << "Компонент " << i + 1 << ": ";
        for (int v : scc[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> grath = create_smej_list();
    print_smej_list(grath); 
    
    //Задача 1 Дан ориентированный граф. Вывести количество вершин, смежных с данной.
    //int x;
    //cout << "Введите вершину для поиска смежных" << endl; cin >> x;
    //cout << cin_ver(grath, x) << endl;

    //Задача 2 Дан ориентированный граф. Вставить в граф ребро, соединяющее вершины A и B.
    /*int a, b;
    cout << "Введите 2 вершины a и b, между которыми нужно добавить ребро" << endl; cin >> a >> b;
    add_reb(grath, a, b);
    print_smej_list(grath);*/

    //Задача 3 Дан неориентированный граф. Подсчитать степень каждой вершины.
    /*print_step(grath);*/

    //Задача 4 Дан ориентированный граф. Вывести все вершины, недостижимые из данной.
    /*int x;
    cout << "Введите текущую вершину" << endl; cin >> x;
    print_unreach(grath, x);*/

    //Задача 5 Дан ориентированный граф. Найти все сильно связные компоненты графа.
    vector<vector<int>> scc = find_scc(grath);
    print_scc(scc);
    return 0;
}