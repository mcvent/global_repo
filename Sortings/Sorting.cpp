#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<sstream>
#include <algorithm>
using namespace std;
vector<vector<int>> reading(const string& filename) {
    vector<vector<int>> sp;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        int number;
        while (ss >> number) {
            row.push_back(number);
        }
        sp.push_back(row);
    }
    file.close();
    return sp;
}
void printing(const vector<vector<int>>& sp) {
    for (const auto& row : sp) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}
void write(const vector<vector<int>>& sp, const string& filename) {
    ofstream file(filename);
    for (const auto& row : sp) {
        for (int num : row) {
            file << num << " ";
        }
        file << endl;
    }
    file.close();
}


//Быстрая
void quickSort(vector<vector<int>>& arr, int L, int R, int col) {
    if (L >= R) return;
    int i = L;
    int j = R;
    // Выбираем опорный элемент (середина столбца)
    int pivot = arr[(L + R) / 2][col];
    // Разделение столбца
    while (i <= j) {
        while (arr[i][col] < pivot) i++; // Ищем элемент больше опорного слева
        while (arr[j][col] > pivot) j--; // Ищем элемент меньше опорного справа

        if (i <= j) {
            swap(arr[i][col], arr[j][col]);
            i++;
            j--;
        }
    }
    // Рекурсивно сортируем левую и правую части столбца
    if (L < j) quickSort(arr, L, j, col);
    if (i < R) quickSort(arr, i, R, col);
}
void quicksortCol(vector<vector<int>>& sp) {
    int rows = sp.size();    // Количество строк
    int cols = sp[0].size(); // Количество столбцов
    for (int col = 0; col < cols; col++) {  
        quickSort(sp, 0, rows - 1, col); 
    }
}
//Расчёска
void combSort(vector<int>& sp, bool направление = true) {
    int n = sp.size();
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13; // Уменьшаем gap
        if (gap < 1) gap = 1;

        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if ((направление && sp[i] > sp[i + gap]) || (!направление && sp[i] < sp[i + gap])) {
                swap(sp[i], sp[i + gap]);
                swapped = true;
            }
        }
    }
}
void sortCol(vector<vector<int>>& sp) {
    int rows = sp.size();
    int cols = sp[0].size();

    for (int col = 0; col < cols; col++) {
        // Извлекаем столбец
        vector<int> column(rows);
        for (int row = 0; row < rows; row++) {
            column[row] = sp[row][col];
        }       
        // Сортируем столбец
        if ((col + 1) % 3 == 0) {
            // Каждый третий столбец сортируем по убыванию
            combSort(column, false);
        }
        else {
            // Остальные столбцы сортируем по возрастанию
            combSort(column, true);
        }
        for (int row = 0; row < rows; row++) {
            sp[row][col] = column[row];
        }
    }
}
// Чёт-нечет    
void Чёт_нечет(vector<int>& arr) {
    int n = arr.size();
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        // Чётная фаза
        for (int i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        // Нечётная фаза
        for (int i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
}
void sortD(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Сортировка диагоналей выше и включая главную диагональ
    for (int k = 0; k < n; k++) {
        vector<int> diagonal;
        int i = 0, j = k;
        while (i < n && j < n) {
            diagonal.push_back(matrix[i][j]);
            i++;
            j++;
        }
        Чёт_нечет(diagonal);
        // Возвращаем отсортированные элементы на диагональ
        i = 0, j = k;
        int idx = 0;
        while (i < n && j < n) {
            matrix[i][j] = diagonal[idx++];
            i++;
            j++;
        }
    }
    // Сортировка диагоналей ниже главной диагонали
    for (int k = 1; k < n; k++) {
        vector<int> diagonal;
        int i = k, j = 0;
        // Собираем элементы диагонали
        while (i < n && j < n) {
            diagonal.push_back(matrix[i][j]);
            i++;
            j++;
        }
        Чёт_нечет(diagonal);
        // Возвращаем отсортированные элементы на диагональ
        i = k, j = 0;
        int idx = 0;
        while (i < n && j < n) {
            matrix[i][j] = diagonal[idx++];
            i++;
            j++;
        }
    }
}



int main()
{   
    setlocale(LC_ALL, "ru");
    vector<vector<int>> nums = reading("inf.txt");
    //printing(nums);
    //quicksortCol(nums);
    //sortCol(nums);
    sortD(nums);
    //printing(nums);
    write(nums, "sorted.txt");
    return 0;
}