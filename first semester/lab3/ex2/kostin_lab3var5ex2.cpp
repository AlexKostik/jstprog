#include <iostream>
using namespace std;

int main() {
    int grade;
    
    cout << "Введите оценку от 1 до 5: ";
    cin >>  grade;
    
    if (cin.fail()) {
        cout << "Введено не число" << endl;
        return 1;
    }
    switch (grade) {
        case 1:
            cout << "Очень плохо" << endl;
            break;
        case 2:
            cout << "Неудовлетворительно" << endl;
            break;
        case 3:
            cout << "Удовлетворительно" << endl;
            break;
        case 4:
            cout << "Хорошо" << endl;
            break;
        case 5:
            cout << "Отлично" << endl;
            break;
        default:
            cout << "Оценка должна быть от 1 до 5" << endl;
            break;
    }
    return 0;
}