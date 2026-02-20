#include <iostream>
#include <cmath>
using namespace std;

// Функция для вычисления растояния между двумя точками 
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Функция вычисления площади по формуле Герона
double area(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = distance(x1, y1, x2, y2);
    double b = distance(x2, y2, x3, y3);
    double c = distance(x3, y3, x1, y1);
    double p = (a + b + c) / 2; // Полупериметр
    double s2 = p * (p - a) * (p - b) * (p - c);
    if (s2 <= 0) return 0;
    return sqrt(s2);
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    double x4, y4, x5, y5, x6, y6;

    cout << "Введите координаты первого треугольника (x1 y1 x2 y2 x3 y3): ";
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    cout << "Введите координаты второго треугольника (x4 y4 x5 y5 x6 y6): ";
    cin >> x4 >> y4 >> x5 >> y5 >> x6 >> y6;

    double S1 = area(x1, y1, x2, y2, x3, y3);
    double S2 = area(x4, y4, x5, y5, x6, y6);

    cout << "Площадь первого треугольника: " << S1 << endl;
    cout << "Площадь второго треугольника: " << S2 << endl;

    if (S1 <= 0 || S2 <= 0) {
        cout << "Один или оба треугольника не существуют." << endl;
    } else if (S1 > S2) {
        cout << "Первый треугольник имеет большую площадь." << endl;
    } else if (S2 > S1) {
        cout << "Второй треугольник имеет большую площадь." << endl;
    } else {
        cout << "Оба треугольника имеют равные площади." << endl;
    }
    return 0;
}