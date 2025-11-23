#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//========== Структура книги ==========
struct Book {
    string title;
    string author;
};

int main() {

//============ Массив книг ============
    const int MAX_BOOKS = 10;
    Book library[MAX_BOOKS];
    int bookCount = 0;

//======== Чтение книг из файла =======
    ifstream inputFile("library.txt");
    if (!inputFile.is_open()) {
        ofstream createFile("library.txt");
        createFile.close();
        ifstream inputFile("library.txt");
    }

//======== Загрузка книг в массив =======
    while (getline(inputFile, library[bookCount].title, '-') &&
           getline(inputFile, library[bookCount].author)) {
        bookCount++;
        if (bookCount >= MAX_BOOKS) break;
    }
    inputFile.close();

//======== Вывод текущих книг ========
    cout << "Текущий список книг:\n";
    for (int i = 0; i < bookCount; ++i) {
        cout << i + 1 << ". " << library[i].title << " - " << library[i].author << endl;
    }

//======== Ввод новой книги ===========
    string newTitle, newAuthor;
    cout << endl << "Введите название новой книги: ";
    getline(cin, newTitle);
    cout << "Введите автора книги: ";
    getline(cin, newAuthor);
    Book newBook = {newTitle, newAuthor};

//======= Сдвиг и добавление =========
    for (int i = bookCount; i > 0; --i) {
        library[i] = library[i - 1];
    }
    library[0] = newBook;
    bookCount++;

//======== Запись обновленных книг в файл ========
    ofstream outputFile("library.txt");
    if (!outputFile.is_open()) {
        cout << "Не удалось открыть файл для записи." << endl;
        return 1;
    }
    for (int i = 0; i < bookCount; ++i) {
        outputFile << library[i].title << " - " << library[i].author << endl;
    }
    outputFile.close();
    cout << "\nКнига сохранена в файл." << endl;

// ======= Вывод всех книг ============
    cout << "\nТекущий список книг:\n";
    for (int i = 0; i < bookCount; ++i) {
        cout << i + 1 << ". " << library[i].title << " - " << library[i].author << endl;
    }
}