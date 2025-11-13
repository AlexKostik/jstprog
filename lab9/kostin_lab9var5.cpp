#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//========== Структура книги ==========
struct Book {
    string title;
    string author;
};


int main() {

//============ Открытие файла ============
    string filename = "library.txt";
    fstream file(filename);
    file.open("library.txt", ios::in | ios::out | ios::app);
    if (!file) {
        cout << "Ошибка открытия файла " << filename << endl;
        return 1;
    }

//========== Чтение книг из файла ========
    const int MAX_BOOKS = 4;
    Book library[MAX_BOOKS];
    string line;
    int count = 0;

    while (getline(file, line) && count < MAX_BOOKS) {
        size_t delimiterPos = line.find(" - ");
        if (delimiterPos != string::npos) {
            library[count].title = line.substr(0, delimiterPos);
            library[count].author = line.substr(delimiterPos + 3);
            count++;
        }
    }

// ======= Вывод текущих книг из файла ========
    while (!file.eof()) {
        string line;
        getline(file, line);
        cout << line << endl;
    }

//======== Ввод новой книги в файл ===========
    string newTitle, newAuthor;
    file.seekg(0);
    file << endl << "Введите название новой книги: ";
    getline(cin, newTitle);
    file << newTitle << endl;
    cout << "Введите автора книги: ";
    getline(cin, newAuthor);
    file << newAuthor << endl;
    Book newBook = {newTitle, newAuthor};

//======= Сдвиг и добавление =========
    for (int i = MAX_BOOKS - 1; i > 0; --i) {
        library[i] = library[i - 1];
    }
    library[0] = newBook;

//======== Вывод всех книг ============
    cout << "\nТекущий список книг:\n";
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (!library[i].title.empty()) {
            cout << i + 1 << ". " << library[i].title << " - " << library[i].author << endl;
        }
    }
    file.close();
    return 0;
}