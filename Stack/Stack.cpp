#include<iostream>

using namespace std;
//struct queue {
//    int inf;
//    queue* next;
//};
//void push(queue*& h, queue*& t, int x) { //вставка элемента в очередь
//    queue* r = new queue;    //создаем новый элемент
//    r->inf = x;
//    r->next = NULL;    //всегда последний
//    if (!h && !t) {    //если очередь пуста
//        h = t = r;    //это и голова и хвост
//    }
//    else {
//        t->next = r;    //r - следующий для хвоста
//        t = r;    //теперь r - хвост
//    }
//}
//int pop(queue*& h, queue*& t) { //удаление элемента из очереди
//    queue* r = h;    //создаем указатель на голову
//    int i = h->inf;    //сохраняем значение головы
//    h = h->next;    //сдвигаем указатель на следующий элемент
//    if (!h)    //если удаляем последний элемент из очереди
//        t = NULL;
//    delete r;    //удаляем первый элемент
//    return i;
//}
//
//void findthepos(queue* h, queue* t, int x, int& f1, int& f2, queue*& h2, queue*& t2) {
//    f1 = f2 = -1;
//    int pos = 0;
//    queue* h1 = NULL, * t1 = NULL; //temp
//
//
//    while (h) {//сначала перекладываем элементы в temp 
//        push(h1, t1, pop(h, t));
//    }
//    while (h1) {
//        int current = pop(h1, t1);
//        push(h2, t2, current);
//        //cout << current;
//        if (current == x) {
//            if (f1 == -1) {
//                f1 = pos;
//            }
//            f2 = pos;
//        }
//        pos++;
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "RU");
//    int n; cin >> n;
//    queue* h = NULL, * t = NULL;
//    int min = 1000000;
//    cout << "Введите n элементов: "; int x;
//    for (int i = 0; i < n; ++i) {
//        cin >> x;
//        if (x < min) min = x;
//        push(h, t, x); //заполняем очередь
//    }
//
//    queue* h2 = NULL, * t2 = NULL; //temp 
//    int first_min_pos, last_min_pos;
//    findthepos(h, t, min, first_min_pos, last_min_pos, h2, t2);
//    //cout << first_min_pos << endl << last_min_pos << endl;
//    queue* new_h = NULL, * new_t = NULL;
//    queue* r = h2;
//    int pos = 0;
//    while (h2) {
//        int current = pop(h2, t2); 
//        if (pos != first_min_pos && pos != last_min_pos) {
//            push(new_h, new_t, current); 
//        }
//        pos++;
//    }
//
//    cout << "Итог: ";
//    while (new_h) {
//        cout << pop(new_h, new_t) << " ";
//    }
//    cout << endl;
//    return 0;
//}
//Задача 3
//struct stack {
//    int inf;
//    stack* next;
//};
//
//void push(stack*& h, char x) {
//    stack* r = new stack; 
//    r->inf = x; 
//    r->next = h; 
//    h = r; 
//
//}
//
//int pop(stack*& h) {
//    int i = h->inf;
//    stack* r = h;
//    h = h->next;
//    delete r;
//    return i;
//
//}
//
//void reverse(stack*& h) {//"обращение"стека
//        stack* head1 = NULL;
//        while (h)
//            push(head1, pop(h));
//        h = head1;
//    }
//bool isPrime(int n) {
//    if (n <= 1) return false;
//    if (n == 2) return true;
//    if (n % 2 == 0) return false;
//    for (int i = 3; i * i <= n; i += 2)
//        if (n % i == 0) return false;
//    return true;
//}
//stack* result(stack*& h) {
//    stack* t = NULL;
//    stack* res = NULL;
//
//    while (h) {//сначала перекладываем элементы в temp 
//        push(t, pop(h));
//    }
//    while (t) {
//        int current = pop(t);
//        if (!isPrime(current)) {
//            push(res, current);
//        }
//    }
//
//    return res;
//}
//int main() {
//    setlocale(LC_ALL, "RU");
//    int n;
//    cin >> n;
//    stack* st = NULL;
//    int x;
//    cout << "'элементы: ";
//    for (int i = 0; i < n; i++) {
//        cin >> x;
//        push(st, x);
//    }
//    reverse(st); 
//    stack* res = result(st);
//
//    while (res)
//        cout << pop(res) << " ";
//    cout << endl;
//
//    return 0;
//}
//Задача 2
struct stack {
    char inf;
    stack* next;
};

void push(stack*& h, char x) {
    stack* r = new stack; 
    r->inf = x; 
    r->next = h; 
    h = r; 

}

char pop(stack*& h) {
    char i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;

}

void reverse(stack*& h) {//"обращение"стека
    stack* head1 = NULL;
    while (h)
        push(head1, pop(h));
    h = head1;
}

bool isglasn(char n) {
    return (n == 'a' || n == 'u' || n == 'e' || n == 'y' || n == 'o' || n == 'i');
}

stack* result(stack*& h) {
    stack* tmp = NULL;
    stack* res = NULL;
    bool f = true;
    char newl = '?';

    while (h) {//сначала перекладываем элементы в temp 
        push(tmp, pop(h));
    }
    while (tmp) {
        char current = pop(tmp);
        if (isglasn(current) && f) {
            push(res, current);
            push(res, newl);
            f = false;
        }
        else {
            push(res, current);
        }
    }

    return res;
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cin >> n;
    stack* head = NULL;
    char x;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(head, x);
    }
    stack* res = result(head);//результат
    reverse(res);
    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}


//Задача 4
//struct queue {
//    int inf;
//    queue* next;
//};
//void push(queue*& h, queue*& t, int x) { 
//    queue* r = new queue;   
//    r->inf = x;
//    r->next = NULL;  
//    if (!h && !t) {   
//        h = t = r;  
//    }
//    else {
//        t->next = r;    
//        t = r;   
//    }
//}
//int pop(queue*& h, queue*& t) {
//    queue* r = h; 
//    int i = h->inf; 
//    h = h->next;    
//    if (!h)    
//        t = NULL;
//    delete r;    //удаляем первый элемент
//    return i;
//}
//// Функция циклического сдвига
//void сдвиг(queue*& h, queue*& t) {
//    if (!h) return;
//
//    queue* tmp_h = NULL, * tmp_t = NULL;
//    bool found = false;
//    int f = -1;
//    int pos = 0;
//
//    // Находим позицию первого нечетного элемента
//    queue* m = h;
//    while (m) {
//        if (m->inf % 2 != 0) {
//            f = pos;
//            break;
//        }
//        m = m->next;
//        pos++;
//    }
//    // Переносим элементы до первого нечетного в конец
//    for (int i = 0; i < f; ++i) {
//        push(h, t, pop(h, t));
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "RU");
//    int n; cin >> n;
//    queue* h = NULL, * t = NULL;
//    cout << "Введите n элементов: "; int x;
//    for (int i = 0; i < n; ++i) {
//        cin >> x;
//        push(h, t, x); //заполняем очередь
//    }
//
//    сдвиг(h, t);
//
//    while (h) {
//        cout << h->inf << " ";
//        h = h->next;
//    }
//    cout << endl;
//    return 0;
//}