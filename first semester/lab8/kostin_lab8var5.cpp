#include <iostream>
#include <string>
using namespace std;

//========== Структура книги ==========
struct Book {
    string title;
    string author;
};

int main() {

//============ Массив книг ============
    const int MAX_BOOKS = 4;
    Book library[MAX_BOOKS] = {
        {"Война и мир", "Лев Толстой"},
        {"Зеленая миля", "Стивен Кинг"},
        {"Мастер и Маргарита", "Михаил Булгаков"}
    };

//======== Вывод текущих книг ========
    cout << "Текущий список книг:\n";
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (!library[i].title.empty()) {
            cout << i + 1 << ". " << library[i].title << " - " << library[i].author << endl;
        }
    }

//======== Ввод новой книги ===========
    string newTitle, newAuthor;
    cout << endl << "Введите название новой книги: ";
    getline(cin, newTitle);
    cout << "Введите автора книги: ";
    getline(cin, newAuthor);
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
}