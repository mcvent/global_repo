#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;
//дерево
struct tree {
    char inf;
    tree* left;
    tree* right;
    tree* parent;
};
//стек
struct stack {
    tree* inf;
    stack* next;
};
void push(stack*& h, tree* x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}
tree* pop(stack*& h) {
    tree* i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

//функция для нового узла
tree* elem(char x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}
//приоритет выполнения
int prior(char oper) {
    if (oper == '(') return 1;
    if (oper == '+' || oper == '-') return 2;
    if (oper == '*' || oper == '/') return 3;
    return 0;
}

//Функция построения дерева из выражения
tree* create_tree(string str) {
    stack* s = NULL; stack* elems = NULL;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') continue;
        if (isdigit(str[i])) {
            push(elems, elem(str[i]));
        }
        else if (str[i] == '(') {
            push(s, elem(str[i]));
        }
        else if (str[i] == ')') {
            while (s && s->inf->inf != '(') {
                tree* opr = pop(s);
                opr->right = pop(elems);
                opr->left = pop(elems);
                push(elems, opr);
            }
            pop(s);
        }
        else {
            while (s && prior(s->inf->inf) >= prior(str[i])) {
                tree* opr = pop(s);
                opr->right = pop(elems);
                opr->left = pop(elems);
                push(elems, opr);
            }
            push(s, elem(str[i]));
        }
    }
    while (s) {
        tree* ops = pop(s);
        ops->right = pop(elems);
        ops->left = pop(elems);
        push(elems, ops);
    }
    return pop(elems);
}
void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width && szOfConsole.Y < height)
        cout << "Please increase the height and width of the terminal. ";
    else if (szOfConsole.X < width)
        cout << "Please increase the width of the terminal. ";
    else if (szOfConsole.Y < height)
        cout << "Please increase the height of the terminal. ";

    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Size of your terminal now: " << szOfConsole.X << ' ' << szOfConsole.Y
            << ". Minimum required: " << width << ' ' << height << ".\n";
        return false;
    }
    return true;
}
void print_helper(tree* x, const COORD pos, const short offset) {
    if (!x) return;

    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}
void print_tree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max);
        short width = 1 << (max + 1);
        short max_w = 128;
        if (width > max_w) width = max_w;

        while (!isSizeOfConsoleCorrect(width, max)) system("pause");

        for (short i = 0; i < max; ++i) cout << '\n';


        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
}
//префиксный обход
void pref (tree* tr) {
    if (tr) {
        cout << tr->inf;
        pref(tr->left);
        pref(tr->right);
    }
}
//постфиксный обход
void post(tree* tr) {
    if (tr) {
        post(tr->left);
        post(tr->right);
        cout << tr->inf;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    string math; string alph = "+-*/()0123456789 ";
    cout << "Введите математическое выражение: ";
    getline(cin, math);
    tree* tr = create_tree(math);
    print_tree(tr);
    
    cout << endl << "Префикс: ";
    pref(tr);
    cout << endl << "Постфикс: ";
    post(tr);

    return 0;
}