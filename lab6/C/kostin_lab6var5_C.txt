#include <iostream>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 256;
    char str[SIZE];

    cout << "Введите строку: ";
    cin.getline(str, SIZE);

    char *word = strtok(str, " ");  // разбиваем по пробелам
    char *minWord = nullptr;
    char *maxWord = nullptr;

    while (word != nullptr) {
        if (minWord == nullptr || strlen(word) < strlen(minWord)) minWord = word;
        if (maxWord == nullptr || strlen(word) > strlen(maxWord)) maxWord = word;
        word = strtok(nullptr, " ");
    }

    if (minWord && maxWord) {
        cout << "Самое короткое слово: " << minWord << endl;
        cout << "Самое длинное слово: " << maxWord << endl;
    } else {
        cout << "Строка пустая или слов нет!" << endl;
    }

    return 0;
}