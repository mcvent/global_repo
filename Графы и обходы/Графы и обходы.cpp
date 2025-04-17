#include <iostream>
#include <vector>
using namespace std;

//очередь
struct queue_node {
	int inf;
	queue_node* next;
};
void queue_push(queue_node*& h, queue_node*& t, int x) {
	queue_node* r = new queue_node;
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
int queue_pop(queue_node*& h, queue_node*& t) {
	queue_node* r = h;
	int i = h->inf;
	h = h->next;
	if (!h) t = NULL;
	delete r;
	return i;
}


//Стек
struct stack_node {
	int inf;
	stack_node* next;
};
void stack_push(stack_node*& h, int x) {
	stack_node* r = new stack_node;
	r->inf = x;
	r->next = h;
	h = r;
}
int stack_pop(stack_node*& h) {
	int i = h->inf;
	stack_node* r = h;
	h = h->next;
	delete r;
	return i;
}


//обход в ширину
vector<int> width(vector<vector<int>>& graph, int start) {
	vector<int> res;
	vector<bool> visited(graph.size(), false);
	queue_node* head = NULL, * tail = NULL;

	queue_push(head, tail, start);
	visited[start] = true;

	while (head) {
		int current = queue_pop(head, tail);
		res.push_back(current);

		for (int neighbor : graph[current]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				queue_push(head, tail, neighbor);
			}
		}
	}

	return res;
}

//нерекурсивный обход в глубину
vector<int> depth(vector<vector<int>>& graph, int x) {
	vector<int> res;
	vector<bool> visited(graph.size(), false);
	stack_node* stack = NULL;

	stack_push(stack, x);
	visited[x] = true;

	while (stack) {
		int current = stack_pop(stack);
		res.push_back(current);

		for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it) {
			if (!visited[*it]) {
				visited[*it] = true;
				stack_push(stack, *it);
			}
		}
	}

	return res;
}
int main() {
	setlocale(LC_ALL, "RU");
	//граф в виде списка смежности
	vector<vector<int>> graph = {
		{1, 2}, //0 имеет связь с 1 и 2
		{0, 3, 4}, //1 имеет связь с 0, 3 и 4
		{0, 5}, //...
		{1},
		{1, 5},
		{2, 4}
	};

	cout << "Результат обхода в ширину: ";
	vector<int> width_result = width(graph, 0);
	for (int x : width_result) {
		cout << x << " ";
	}
	cout << endl;

	cout << "Результат нерекурсивного обхода в глубину: ";
	vector<int> depth_result = depth(graph, 0);
	for (int x : depth_result) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}