#include <iostream>
#include <cstdio>
#include <format>
#include <cmath>
using namespace std;

int main() {
    float x,y,z, result;
    
    printf("Введите значение X, Y, Z (через пробел): ");
    scanf("%f %f %f", &x, &y, &z); // Ввод значений
    float a1,a2, a, b;
    
    // Решение задачи
    a1=pow(cos(x)-sin(y),3);
    a2=sqrt(tan(z));
    a=a1/a2;
    b=pow(log(x*y*z),2);
    result=a+b;
    
  cout << format("e = {}", result); // Вывод результата
}