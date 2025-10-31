#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
    // генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-25, 25); 

    int m;
    cout << "Введите размер вектора (m): ";
    cin >> m;

    if (!cin || m <= 0) {
        cerr << "Ошибка: введите положительное число." << endl;
        return 1;
    }

    // Создание и заполнение вектора случайными числами
    vector<int> x(m);
    cout << "Исходный вектор: ";
    for (int i = 0; i < m; i++) {
        x[i] = dist(gen); // равномерное распределение
        cout << x[i] << " ";
    }
    cout << endl;

    int maxPos = 0;
    for (int i = 1; i < m; i++) {
        if (x[i] > x[maxPos]) {
            maxPos = i;
        }
    }

    for (int i = 0; i < maxPos; i++) {
        x[i] = 0;
    }

    cout << "Вектор после замены: ";
    for (int i = 0; i < m; i++) {
        cout << x[i] << " ";
    }
    cout << endl;

    return 0;
}