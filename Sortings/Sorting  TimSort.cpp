#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Реализация алгоритма сортировки Timsort
int m_r(int n) {//вычисляем min_run (поставим n>=8, чтобы использовать функцию слияния)
    int r = 0;
    // Пока n >= 8, вычисляем min_run
    while (n >= 8) {
        // Если n нечетное, устанавливаем флаг r в 1
        if (n % 2 != 0) {
            r = 1;
        }
        n = n / 2;
    }
    // Возвращаем min_run (n + r, где r может быть 0 или 1)
    return n + r;
}

// Функция сортировки вставками для подмассива от left до right
void insertionSort(vector<int>& sp, int left, int right) {//сортировка вставками
    // Проходим по всем элементам подмассива
    for (int i = left + 1; i <= right; i++) {
        int t = sp[i]; // Запоминаем текущий элемент
        int j = i - 1;
        // Сдвигаем элементы больше t вправо
        while (j >= left && sp[j] > t) {
            sp[j + 1] = sp[j];
            j--;
        }
        // Вставляем t в правильную позицию
        sp[j + 1] = t;
    }
}

// Функция слияния двух отсортированных подмассивов
void merge(vector<int>& sp, int left, int mid, int right) {//слияние
    // Вычисляем длины левого и правого подмассивов
    int len1 = mid - left + 1, len2 = right - mid;
    // Создаем временные массивы для левой и правой частей
    vector<int> leftsp(len1), rightsp(len2);

    // Копируем данные во временные массивы
    for (int i = 0; i < len1; i++) leftsp[i] = sp[left + i];
    for (int i = 0; i < len2; i++) rightsp[i] = sp[mid + 1 + i];

    int i = 0, j = 0, k = left; // Индексы для левого, правого массивов и основного
    // Слияние левого и правого массивов обратно в основной массив
    while (i < len1 && j < len2) {
        if (leftsp[i] <= rightsp[j]) {
            sp[k] = leftsp[i];
            i++;
        }
        else {
            sp[k] = rightsp[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы левого массива (если есть)
    while (i < len1) sp[k++] = leftsp[i++];
    // Копируем оставшиеся элементы правого массива (если есть)
    while (j < len2) sp[k++] = rightsp[j++];
}
void timsort(vector<int>& sp) {//основная функция для тимсорта
    int n = sp.size();
    // Вычисляем minrun
    int minRun = m_r(n);
    // Сортируем подмассивы размером minRun с помощью сортировки вставками
    for (int i = 0; i < n; i += minRun) {//сортировка массивов размером minrun
        insertionSort(sp, i, min(i + minRun - 1, n - 1));
    }
    // Постепенно увеличиваем размер слияемых подмассивов
    for (int size = minRun; size < n; size = 2 * size) {//слияние подмассивов
        // Сливаем подмассивы попарно
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            // Если есть что сливать, вызываем merge
            if (mid < right) {
                merge(sp, left, mid, right);
            }
        }
    }
}

// Главная функция программы
int main() {
    setlocale(LC_ALL, "RU");
    int n, x;
    cout << "n "; // Запрашиваем количество элементов
    cin >> n;
    vector<int> vec;
    // Вводим элементы массива
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++){
        cin >> x;
        vec.push_back(x);
    }
    // Сортируем массив с помощью Timsort
    timsort(vec);
    // Выводим отсортированный массив
    for (auto iter = vec.begin(); iter != vec.end(); iter++) {
        cout << *iter << " ";
    }
    return 0;
}