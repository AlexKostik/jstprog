#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    
    int arr[100];
    cout << "Введите " << n << " элементов:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int bubbleArr[100];
    int quickArr[100];
    
    for (int i = 0; i < n; i++) {
        bubbleArr[i] = arr[i];
        quickArr[i] = arr[i];
    }
    
    cout << "\nПузырьковая сортировка: ";
    bubbleSort(bubbleArr, n);
    for (int i = 0; i < n; i++) {
        cout << bubbleArr[i] << " ";
    }
    cout << endl;
    
    cout << "Быстрая сортировка: ";
    quickSort(quickArr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << quickArr[i] << " ";
    }
    cout << endl;
    
    return 0;
}