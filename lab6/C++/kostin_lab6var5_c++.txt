#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int len_string(string s) {
    int cnt = 0;
    for (char c : s) {
        if((c & 0xC0) != 0x80)
            cnt++;
    }
    return cnt;
}

int main() {
    string line;
    cout << "Введите строку: ";
    getline(cin, line);

    istringstream ss(line);
    string word;
    string minWord, maxWord;

    bool firstWord = true;
    while (ss >> word) {
        if (firstWord) {
            minWord = word;
            maxWord = word;
            firstWord = false;
        } else { 
            if (len_string(word) < len_string(minWord)) {
                minWord = word;
            }
            if (len_string(word) > len_string(maxWord)) {
                maxWord = word;
            }
        }
    }
    
    if (!firstWord) {
        cout << "Самое короткое слово: " << minWord << endl;
        cout << "Самое длинное слово: " << maxWord << endl;
    } else {
        cout << "Строка пустая или слов нет!" << endl;
    }
    return 0;
}