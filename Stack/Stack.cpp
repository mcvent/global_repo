#include<iostream>

using namespace std;
//struct queue {
//	int inf;
//	queue* next;
//};
//void push(queue*& h, queue*& t, int x){ //вставка элемента в очередь
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
//void findthepos(queue* h, queue*& t, int x, int& f1, int& f2) {
//    f1 = f2 = -1;
//    int pos = 0;
//    while (h) {
//        if (h->inf == x) {
//            if (f1 == -1) {
//                f1 = pos;
//            }
//            f2 = pos;
//        }
//        h = h->next;
//        pos++;
//    }
//}
//int findmin(queue* h) {
//    int min = 1000000;
//    while (h) {
//        if (h->inf < min) {
//            min = h->inf;
//        }
//        h = h->next;
//    }
//    return min;
//}
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
//
//    int first_min_pos, last_min_pos;
//    int min = findmin(h);
//    findthepos(h,t,min, first_min_pos, last_min_pos);
//    cout << first_min_pos << endl << last_min_pos << endl;
//    
//    queue* new_h = NULL, * new_t = NULL;
//    queue* current = h;
//    int pos = 0;
//    while (current) {
//        if (pos != first_min_pos && pos != last_min_pos) {
//            push(new_h, new_t, current->inf);
//        }
//        current = current->next;
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
//void push(stack*& h, int x) {
//    stack* r = new stack; //создаем новый элемент
//    r->inf = x; //поле inf = x
//    r->next = h; //следующим элементов является h
//    h = r; //теперь r является головой
//
//}
//int pop(stack*& h) {
//    int i = h->inf;//значение первого элемента
//    stack* r = h;//указатель на голову стека
//    h = h->next;//переносим указатель на следующий элемент
//    delete r;//удаляем первый элемент
//    return i;//возвращаем значение
//
//}
//
//void reverse(stack*& h) {//"обращение"стека
//    stack* head1 = NULL;//инициализация буферного стека
//    while (h)//пока стек не пуст
//        push(head1, pop(h));//переписываем из одного стека в другой
//    h = head1;//переобозначаем указатели
//}
//bool isPrime(int n) {//функция для проверки на простое число
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
//    int n, m;
//    cin >> n;
//    stack* st = NULL;
//    int x;
//    cout << "'элементы: ";
//    for (int i = 0; i < n; i++) {
//        cin >> x;
//        push(st, x);
//    }
//    reverse(st);//переворачиваем стек
//    stack* res = result(st);//результат
//
//    while (res)
//        cout << pop(res) << " ";
//    cout << endl;
//
//    return 0;
//}

//Задача 2
struct stack {
    int inf;
    stack* next;
};

void push(stack*& h, int x) {
    stack* r = new stack; //создаем новый элемент
    r->inf = x; //поле inf = x
    r->next = h; //следующим элементов является h
    h = r; //теперь r является головой

}

int pop(stack*& h) {
    int i = h->inf;//значение первого элемента
    stack* r = h;//указатель на голову стека
    h = h->next;//переносим указатель на следующий элемент
    delete r;//удаляем первый элемент
    return i;//возвращаем значение

}

void reverse(stack*& h) {//"обращение"стека
    stack* head1 = NULL;//инициализация буферного стека
    while (h)//пока стек не пуст
        push(head1, pop(h));//переписываем из одного стека в другой
    h = head1;//переобозначаем указатели
}

bool isPrime(int n) {//функция для проверки на простое число
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

stack* result(stack*& h, int m) {
    stack* temp = NULL;
    stack* res = NULL;
    int newl = m;

    while (h) {//сначала перекладываем элементы в temp 
        push(temp, pop(h));
    }
    while (temp) {
        int current = pop(temp);
        if (isPrime(current)) {
            push(res, current);
            push(res, newl);
        }
        else {
            push(res, current);
        }
    }

    return res;
}

int main() {
    int n, m;
    cout << "n = ";
    cin >> n;
    stack* head = NULL;
    int x;
    cout << "elements: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(head, x);
    }
    cout << "new element: ";
    cin >> m;
    reverse(head);//переворачиваем стек

    stack* res = result(head, m);//результат

    while (res)
        cout << pop(res) << " ";
    cout << endl;

    return 0;
}


//Задача 4
struct queue {
	int inf;
	queue* next;
};
void push(queue*& h, queue*& t, int x){ //вставка элемента в очередь
    queue* r = new queue;    //создаем новый элемент
    r->inf = x;
    r->next = NULL;    //всегда последний
    if (!h && !t) {    //если очередь пуста
        h = t = r;    //это и голова и хвост
    }
    else {
        t->next = r;    //r - следующий для хвоста
        t = r;    //теперь r - хвост
    }
}
int pop(queue*& h, queue*& t) { //удаление элемента из очереди
    queue* r = h;    //создаем указатель на голову
    int i = h->inf;    //сохраняем значение головы
    h = h->next;    //сдвигаем указатель на следующий элемент
    if (!h)    //если удаляем последний элемент из очереди
        t = NULL;
    delete r;    //удаляем первый элемент
    return i;
}
// Функция циклического сдвига
void сдвиг(queue*& h, queue*& t) {
    if (!h) return;

    queue* tmp_h = NULL, * tmp_t = NULL;
    bool found = false;
    int f = -1;
    int pos = 0;

    // Находим позицию первого нечетного элемента
    queue* m = h;
    while (m) {
        if (m->inf % 2 != 0) {
            f = pos;
            break;
        }
        m = m->next;
        pos++;
    }
    // Переносим элементы до первого нечетного в конец
    for (int i = 0; i < f; ++i) {
        push(h, t, pop(h, t));
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int n; cin >> n;
    queue* h = NULL, * t = NULL;
    cout << "Введите n элементов: "; int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        push(h, t, x); //заполняем очередь
    }

    сдвиг(h, t);

    while (h) {
            cout << h->inf << " ";
            h = h->next;
        }
        cout << endl;
    return 0;
}