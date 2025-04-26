#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
#define RED true
#define BLACK false

struct tree {
    int inf;
    bool color; //цвет узла
    tree* left, * right, * parent; //указактели левого и правого потомков и на родителя

    tree(int val, bool col = RED, tree* p = nullptr, tree* l = nullptr, tree* r = nullptr)
        : inf(val), color(col), parent(p), left(l), right(r) {}
};
tree* root = nullptr; //глобальная переменная для корня

void max_height(tree* node, short& max_depth, short depth = 1) {
    if (depth > max_depth) max_depth = depth;
    if (node->left) max_height(node->left, max_depth, depth + 1);
    if (node->right) max_height(node->right, max_depth, depth + 1);
}

void print_tree(tree* node, COORD pos, short offset) {
    SetConsoleTextAttribute(hConsole, node->color == RED ? 12 : 8);
    SetConsoleCursorPosition(hConsole, pos);
    cout << setw(offset + 1) << node->inf;

    if (node->left) print_tree(node->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (node->right) print_tree(node->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print() {
    if (!root) return;

    short height = 1;
    max_height(root, height);

    short width = 1 << (height + 1);
    const short max_width = 128;
    if (width > max_width) width = max_width;

    // Резервируем место
    for (short i = 0; i < height; ++i) cout << '\n';

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    COORD endPos = consoleInfo.dwCursorPosition;

    print_tree(root, { 0, short(endPos.Y - height) }, width >> 1);

    SetConsoleCursorPosition(hConsole, endPos);
    SetConsoleTextAttribute(hConsole, 7);
}

void left_rotate(tree* x) { //функция для балансировки дерева
    tree* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(tree* x) { //функция для балансировки дерева
    tree* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void insert_help(tree* k) { //"перекрашиваем"(чиним) дерево после вставки
    while (k->parent != nullptr && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            tree* u = k->parent->parent->left;
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    right_rotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                left_rotate(k->parent->parent);
            }
        }
        else {
            tree* u = k->parent->parent->right;
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    left_rotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                right_rotate(k->parent->parent);
            }
        }
        if (k == root) break; //выход из цикла если пришли в корень
    }
    root->color = BLACK; //корень всегда черный
}

void insert(int el) { //функция вставки элемента
    tree* node = new tree(el); //при создании, узел - красный
    tree* y = nullptr; 
    tree* x = root;

    while (x) { //поиск места вставки
        y = x;
        if (node->inf < x->inf) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->inf < y->inf) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nullptr) return;

    insert_help(node); //перекрашиваем дерево
}

void sim_obhod(tree* node) { //обходим дерево симметрично и выводим сортированные значения
    if (node != nullptr) {
        sim_obhod(node->left);
        cout << node->inf << " ";
        sim_obhod(node->right);
    }
}

vector<int> find_path(int x) { //функция поиска пути к элементу
    vector<int> path; //путь
    tree* current = root; //корень
    while (current) {
        path.push_back(current->inf); //добавляем текущий узел в путь
        if (x == current->inf) {
            return path;
        }
        else if (x < current->inf) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return vector<int>(); // Путь не найден
}
int main() {
    setlocale(LC_ALL, "RU");
    //вставка элементов в дерево
    vector<int> nums = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
    for (int num : nums) {
        insert(num);
    }

    cout << "Визуализация дерева: " << endl;
    print();
    cout << endl;

    //обход
    cout << "Симметричный обход: ";
    sim_obhod(root);
    cout << endl;

    cout << "Визуализация дерева: " << endl;
    print();
    cout << endl;

    //поиск пути до узла
    int c = 13; // пусть ищем путь к этому элементу
    vector<int> path = find_path(c);
    if (!path.empty()) {
        cout << "Путь до " << c << ": ";
        for (int x : path) {
            cout << " -> " << x ;
        }
        cout << endl;
    }
    else {
        cout << "узел не найден!" << endl;
    }

    return 0;
}