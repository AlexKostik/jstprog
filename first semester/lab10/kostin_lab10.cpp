#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    
    int arr[100000];
    cout << endl << "Заполнение массива из " << n << " элементов случайными числами..." << endl;
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    
    int bubbleArr[100000];
    int quickArr[100000];
    
    for (int i = 0; i < n; i++) {
        bubbleArr[i] = arr[i];
        quickArr[i] = arr[i];
    }
    
    // Измерение времени пузырьковой сортировки
    cout << "\n========== Пузырьковая сортировка ==========" << endl;
    auto start_bubble = high_resolution_clock::now();
    bubbleSort(bubbleArr, n);
    auto end_bubble = high_resolution_clock::now();
    duration<double, milli> duration_bubble = end_bubble - start_bubble;
    cout << "Время выполнения: " << duration_bubble.count() << " мс" << endl;
    
    // Измерение времени быстрой сортировки
    cout << "\n========== Быстрая сортировка ==========" << endl;
    auto start_quick = high_resolution_clock::now();
    quickSort(quickArr, 0, n - 1);
    auto end_quick = high_resolution_clock::now();
    duration<double, milli> duration_quick = end_quick - start_quick;
    cout << "Время выполнения: " << duration_quick.count() << " мс" << endl;
    
    cout << "\n========== Сравнение ==========" << endl;
    cout << "Пузырьковая сортировка: " << duration_bubble.count() << " мс" << endl;
    cout << "Быстрая сортировка: " << duration_quick.count() << " мс" << endl;
    if (duration_bubble.count() > duration_quick.count()) {
        cout << "Быстрая сортировка быстрее в " << (duration_bubble.count() / duration_quick.count()) << " раз" << endl;
    } else {
        cout << "Пузырьковая сортировка быстрее в " << (duration_quick.count() / duration_bubble.count()) << " раз" << endl;
    }
    
    return 0;
}