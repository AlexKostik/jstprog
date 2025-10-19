#include <iostream>
#include <cmath>
#include <numbers>
using namespace std;

int main() {
    int A, B, C, h;   // углы треугольника и высота
    double S;         // площадь

    // Ввод углов
    cout << "Введите углы треугольника: ";
    cin >> A >> B >> C;

    // Ввод высоты
    cout << "Введите высоту: ";
    cin >> h;

    // Проверка существования треугольника
    if (A + B + C != 180 || A <= 0 || B <= 0 || C <= 0) {
        cout << "Такого треугольника не существует!" << endl;
        return 0;
    }

    // Переводим угол A в радианы (для функций sin, cos и т.п.)
    double Arad = A * std::numbers::pi / 180.0;

    // Формула площади через высоту:
    // S = (h^2) / (2 * sin(A))
    S = (h * h) / (2 * sin(Arad));

    // Вывод ответа
    cout << "Площадь треугольника = " << S << endl;

    return 0;
}