#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

const int ROWS = 7;
const int COLS = 8;

int main() {
    // генератор случайных чисел
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-25, 25); 

    // создание матрицы
    int matrix[ROWS][COLS];

    // Массив результатов
    int results[2][COLS] = {0};

    // Заполнение матрицы случайными числами и её вывод
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = dist(gen); // Используем распределение
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    // Вычисление суммы и подсчёт положительных элементов в каждом столбце
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            results[0][j] += matrix[i][j];  // Сумма
            if (matrix[i][j] > 0)
                results[1][j]++;  // Количество положительных элементов
        }
    }

    // Вывод результатов
    cout << "\nРезультаты для каждого столбца:" << endl;
    cout << "Столбец: ";
    for (int j = 0; j < COLS; j++)
        cout << setw(5) << j + 1;

    cout << "\nСумма:   ";
    for (int j = 0; j < COLS; j++)
        cout << setw(5) << results[0][j];

    cout << "\nПолож.:  ";
    for (int j = 0; j < COLS; j++)
        cout << setw(5) << results[1][j];

    cout << endl;

    return 0;
}