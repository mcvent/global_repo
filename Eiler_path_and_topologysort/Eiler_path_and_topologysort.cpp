#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//очередь
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
//стек
struct stack {
    int inf;
    stack* next;
};
void push(stack*& h, int x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}
int pop(stack*& h) {
    int i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}
//разворот
void reverse(stack*& h) {
    stack* head1 = NULL;
    while (h)
        push(head1, pop(h));
    h = head1;
}

//ввод графа
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
void printlist(vector<vector<int>>& Gr) {
    cout << endl << "cписок смежности:" << endl;
    for (int i = 0; i < Gr.size(); ++i) {
        cout << i << ": ";
        for (int vertex : Gr[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}
//проверка возможности эйлерова пути
bool is_eylers(vector<vector<int>>& gr, int& start, int& end) {
    vector<int> st(gr.size(), 0);
    for (int i = 0; i < gr.size(); ++i) {
        st[i] = gr[i].size();
    }
    int count = 0;
    start = end = -1;
    for (int i = 0; i < st.size(); ++i) {
        if (st[i] % 2 != 0) {
            count++;
            if (start == -1) start = i;
            else if (end == -1) end = i;
            else return false; //если вдруг имеются более двух вершин с нечетной степенью
        }
    }
    if (count == 0) {
        start = 0; end = -1;
        return true;
    }
    else if (count == 2) {
        return true;
    }
    else {
        return false;
    }
}
//поиск эйлерова пути
void find_path(vector<vector<int>> gr) {
    int start, end;
    if (!is_eylers(gr, start, end)) {
        cout << "Граф не содержит Эйлеров путь" << endl;
        return;
    }
    bool iscycl = (end == -1);
    stack* eyler_path = NULL;
    stack* ver_stack = NULL;
    if (iscycl) {
        push(ver_stack, 0);  //если получился цикл, возращаемся в 0
    }
    else {
        push(ver_stack, start);  //нашли путь = начинаем с начальной вершины
    }
    vector<vector<int>> temp_gr = gr;
    while (ver_stack) {
        int current = ver_stack->inf;
        if (!temp_gr[current].empty()) {
            int next = temp_gr[current].back();
            temp_gr[current].pop_back();
            vector<int>::iterator it = find(temp_gr[next].begin(), temp_gr[next].end(), current);
            if (it != temp_gr[next].end()) {
                temp_gr[next].erase(it);
            }
            push(ver_stack, next);
        }
        else {
            push(eyler_path, pop(ver_stack));
        }
    }

    if (!iscycl) {
        stack* temp = eyler_path;
        int last = -1;
        while (temp) {
            last = temp->inf;
            temp = temp->next;
        }
        if (last != end) {
            reverse(eyler_path);
        }
    }

    if (iscycl) {
        cout << "Эйлеров цикл: ";
    }
    else {
        cout << "Эйлеров путь: ";
    }
    while (eyler_path) {
        cout << pop(eyler_path);
        if (eyler_path) cout << " -> ";
    }
    cout << endl;
}

//рекурсивно проходим по смежным вершинам и пишем их в стек
void topolg_helper(int v, vector<bool>& visited, stack*& result, vector<vector<int>>& gr) {
    visited[v] = true;
    for (size_t i = 0; i < gr[v].size(); i++) {
        int u = gr[v][i];
        if (visited[u] == false) {
            topolg_helper(u, visited, result, gr);
        }
    }
    push(result, v);
}
//топологическая сортировка
void topolog_sort(vector<vector<int>>& gr) {
    stack* res = NULL;
    vector<bool> visited(gr.size(), false);

    for (int i = 0; i < gr.size(); ++i) {
        if (!visited[i])
            topolg_helper(i, visited, res, gr);
    }

    cout << "топологическая сортировка: ";
    while (res) {
        cout << pop(res) << " ";
    }   
    cout << endl;
}

//Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.
//Дан ориентированный граф.Если это возможно, реализовать топологическую сортировку

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Эйлеров путь (неориентированный граф)" << endl;
    vector<vector<int>> graph1 = create_smej_list();
    printlist(graph1);
    find_path(graph1);

    cout << endl << "Топологическая сортировка (ориентированный граф)" << endl;
    vector<vector<int>> graph2 = create_smej_list();
    printlist(graph2);
    topolog_sort(graph2);
    return 0;
}