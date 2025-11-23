#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

const int ROWS = 5;
const int COLS = 5;

int main() {
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100); 

    int matrix[ROWS][COLS];

    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = dist(gen);
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    cout << "\nСуммы элементов в строках:" << endl;
    for (int i = 0; i < ROWS; i++) {
        int rowSum = 0;
        for (int j = 0; j < COLS; j++) {
            rowSum += matrix[i][j];
        }
        cout << "Сумма строки " << i + 1 << ": " << rowSum << endl;
    }

    return 0;
}