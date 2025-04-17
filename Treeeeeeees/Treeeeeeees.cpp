#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
//глобальные переменные для работы с консолью
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;
struct tree {
	int inf;
	tree* left;
	tree* right;
	tree* parent;
};

//создание узла, информационное поле равно x, остальные - NULL
tree* node(int x) {
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = n->parent = NULL;
	return n;
}

//вставка элемента в дерево бинарного поиска
void insert(tree*& tr, int x) {
	tree* n = node(x);
	if (!tr) tr = n; //если дерево пустое - корень
	else {
		tree* y = tr;
		while (y) { //ищем куда вставлять
			if (n->inf > y->inf) { //правая ветка
				if (y->right) y = y->right;
				else {
					n->parent = y; //узел становится правым ребенком
					y->right = n;
					break;
				}
			}
			else if (n->inf < y->inf) { //левая ветка
				if (y->left) y = y->left;
				else {
					n->parent = y; //узел становится левым ребенком
					y->left = n;
					break;
				}
			}
			else { //если элемент уже существует
				delete n;
				break;
			}
		}
	}
}

//поиск элемента в дереве бинарного поиска
tree* find(tree* tr, int x) {
	if (!tr || tr->inf == x) return tr; //нашли или дошли до конца ветки
	if (x < tr->inf)
		return find(tr->left, x); //ищем по левой ветке
	else
		return find(tr->right, x); //ищем по правой ветке
}

//функция для вычисления высоты дерева
//высота узла - максимальная длина пути от узла до листа
void max_height(tree* x, short& max, short deepness = 1) {
	if (deepness > max) max = deepness;
	if (x->left) max_height(x->left, max, deepness + 1);
	if (x->right) max_height(x->right, max, deepness + 1);
}

//функция проверки размера консоли
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
	GetConsoleScreenBufferInfo(outp, &csbInfo);
	COORD szOfConsole = csbInfo.dwSize;
	if (szOfConsole.X < width || szOfConsole.Y < height) {
		cout << "Please increase the size of the terminal. Size now: "
			<< szOfConsole.X << "x" << szOfConsole.Y
			<< ". Minimum required: " << width << "x" << height << ".\n";
		return false;
	}
	return true;
}

//вспомогательная функция для печати дерева
void print_helper(tree* x, const COORD pos, const short offset) {
	SetConsoleCursorPosition(outp, pos);
	cout << right << setw(offset + 1) << x->inf;
	if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
	if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

//основная функция печати дерева
void printTree(tree* tr) {
	if (tr) {
		short max = 1;
		max_height(tr, max); //вычисляем высоту дерева
		short width = 1 << (max + 1); //вычисляем ширину для печати
		short max_w = 128;
		if (width > max_w) width = max_w;

		while (!isSizeOfConsoleCorrect(width, max)) {
			system("pause");
		}

		//резервируем место для вывода
		for (short i = 0; i < max; ++i) cout << '\n';

		GetConsoleScreenBufferInfo(outp, &csbInfo);
		COORD endPos = csbInfo.dwCursorPosition;

		//выводим дерево
		print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
		SetConsoleCursorPosition(outp, endPos);
	}
	else {
		cout << "The tree is empty." << endl;
	}
}
//вывод пути от узла до корня
//void printpath(tree* node) {
//    if (!node) return;
//
//    //cчитаем глубину до корня
//    int depth = 0;
//    tree* current = node;
//    while (current) {
//        depth++;
//        current = current->parent;
//    }
//
//    int* path = new int[depth];
//    int count = 0;
//    current = node;
//    while (current) {
//        path[count++] = current->inf;
//        current = current->parent;
//    }
//    for (int i = count - 1; i >= 0; --i) {//выводим путь от корня к узлу
//        cout << path[i];
//        if (i > 0) cout << " -> ";
//    }
//    cout << endl;
//
//    delete[] path; //освобождаем память
//}
//int main() {
//    setlocale(LC_ALL, "RU");
//    tree* treee = NULL;
//    int n, x;
//    cout << "n: ";
//    cin >> n;
//    cout << "Введите элементы: ";
//    for (int i = 0; i < n; ++i) {
//        cin >> x;
//        insert(treee, x); //вставляем элементы в дерево
//    }
//
//    cout << endl << "вывод" << endl;
//    printTree(treee);
//
//    cout << endl << "x: ";
//    cin >> x;
//
//    tree* target = find(treee, x); //ищем элемент в дереве
//    if (!target) {
//        cout << "Элемент " << x << " не содержится внутри дерева" << endl;
//    }
//    else {
//        cout << "Путь к " << x << ": ";
//        printpath(target); //выводим путь к элементу
//    }
//
//    return 0;
//}

//Дан список целых чисел.Построить дерево бинарного поиска.Найти сумму всех нечетных листьев.Если таких нет, вывести сообщение об этом.
// функция для вычисления суммы нечетных листьев
//int sumevenleaf(tree* treee) {
//	if (!treee) return 0;
//
//	// если это лист (нет детей) и значение нечетное
//	if (!treee->left && !treee->right && treee->inf % 2 != 0) {
//		return treee->inf;
//	}
//
//	// рекурсивно суммируем нечетные листья в левом и правом поддеревьях
//	return sumevenleaf(treee->left) + sumevenleaf(treee->right);
//}
//int main() {
//	setlocale(LC_ALL, "RU");
//	tree* treee = NULL;
//	int n, x;
//
//	cout << "введите количество элементов: ";
//	cin >> n;
//	cout << "Введите элементы: ";
//	for (int i = 0; i < n; ++i) {
//		cin >> x;
//		insert(treee, x); // вставляем элементы в дерево
//	}
//	cout << endl << "вывод" << endl;
//	printTree(treee);
//
//	// находим сумму нечетных листьев
//	int s = sumevenleaf(treee);
//	if (s == 0) {
//		cout << endl << "в дереве нет нечетных листьев." << endl;
//	}
//	else {
//		cout << endl << "сумма нечетных листьев: " << s << endl;
//	}
//
//	return 0;
//}

//Дан список целых чисел. Построить дерево бинарного поиска. Дан узел Х. Если существуют "племянники", то удалить левого из них.
// функция для нахождения и удаления левого племянника
void remove_left_plem(tree* x) {
    if (!x || !x->parent) {
        cout << "у узла нет родителя, поэтому нет и племянников." << endl;
        return;
    }

    tree* parent = x->parent;
    tree* uncle = (parent->left == x) ? parent->right : parent->left;

    if (!uncle) {
        cout << "у узла нет дяди, поэтому нет и племянников." << endl;
        return;
    }

    tree* leftNephew = uncle->left;
    if (!leftNephew) {
        cout << "у дяди нет левого ребенка (племянника)." << endl;
        return;
    }

    //cout << leftNephew->inf << endl;

    if (uncle->left == leftNephew) {
        uncle->left = NULL;
    }
    delete leftNephew;
}
int main() {
    setlocale(LC_ALL, "RU");
    tree* root = NULL;
    int n, x;

    // построение дерева
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(root, x);
    }
    cout << endl << "вывод" << endl;
    printTree(root);

    // поиск узла X
    cout << endl << "Введите значение узла X: ";
    cin >> x;
    tree* target = find(root, x);

    if (!target) {
        cout << "Узел " << x << " не найден в дереве." << endl;
    }
    else {
        // удаление левого племянника
        removeLeftNephew(target);
        printTree(root);
    }

    return 0;
}