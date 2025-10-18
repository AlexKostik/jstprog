#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    float x,y,z, result;
    printf("Введите значение X, Y, Z (через пробел): ");
    scanf("%f %f %f", &x, &y, &z); // Ввод значений
    
    float min = x;
    float max = x;
    
    // Нахождение максимума
    if (y > max) {
        max = y;
    }
    if (z > max) {
        max = z;
    }
    // Нахождение минимума
    if (y < min) {
        min = y;
    }
    
    // Вычисление
    result = max/min + 5;
    
    // Вывод результата
    printf("m = %.2f \n", result);
    return 0;
}