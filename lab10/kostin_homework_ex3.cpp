#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Введите размер матрицы n: ";
    cin >> n;
 
    int a[100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }

    cout << "Матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}