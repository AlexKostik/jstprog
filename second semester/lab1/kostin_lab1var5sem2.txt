#include <iostream>
#include <string>
using namespace std;

struct PatientRecord {
    string fullname;
    int age;
    string doctor;
    string date;
    PatientRecord* prev;
    PatientRecord* next;

    PatientRecord(string f, int a, string d, string dt) {
        this->fullname = f;
        this->age = a;
        this->doctor = d;
        this->date = dt;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class PatientLinkedList {
private:
    PatientRecord* head; // Указатель на первый элемент
    PatientRecord* tail; // Указатель на последний элемент

public:
    //Конструктор, инициализация пустого списка
    PatientLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    // Деструктор (освобождение памяти)
    ~PatientLinkedList() {
        PatientRecord* current = head;
        while (current != nullptr) {
            PatientRecord* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    // Прямой вывод списка
    void add(string fullname, int age, string doctor, string date) {
        PatientRecord* newNode = new PatientRecord(fullname, age, doctor, date);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Отмена записи
    void remove(string fullname) {
        PatientRecord* current = head;

        while (current != nullptr && current->fullname != fullname) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Пациент не найден\n";
            return;
        }

        if (current == head && current == tail) {
            head = tail = nullptr;
        } 
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
        } 
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } 
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        cout << "Запись отменена\n";
    }

    // Изменение врача
    void changeDoctor(string fullname, string newDoctor) {
        PatientRecord* current = head;

        while (current != nullptr) {
            if (current->fullname == fullname) {
                current->doctor = newDoctor;
                cout << "Врач изменен\n";
                return;
            }
            current = current->next;
        }

        cout << "Пациент не найден\n";
    }

    // Поиск пациентов по имени
    void searchByName(string fullname) {
        PatientRecord* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->fullname == fullname) {
                cout << "ФИО: " << current->fullname
                     << ", Возраст: " << current->age
                     << ", Врач: " << current->doctor
                     << ", Дата: " << current->date << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found)
            cout << "Пациент не найден\n";
    }

    // Поиск записи по врачу
    void searchByDoctor(string doctor) {
        PatientRecord* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->doctor == doctor) {
                cout << "ФИО: " << current->fullname
                     << ", Возраст: " << current->age
                     << ", Дата: " << current->date << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found)
            cout << "Записей к этому врачу нет\n";
    }

    // Поиск записи по дате
    void searchByDate(string date) {
        PatientRecord* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->date == date) {
                cout << "ФИО: " << current->fullname
                     << ", Возраст: " << current->age
                     << ", Врач: " << current->doctor << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found)
            cout << "Записей на эту дату нет\n";
    }

    // Вывод всего списка
    void printForward() {
        if (head == nullptr) {
            cout << "Список пуст\n";
            return;
        }

        PatientRecord* temp = head;
        while (temp != nullptr) {
            cout << temp->fullname << " (" << temp->age << "), "
                 << temp->doctor << ", "
                 << temp->date << endl;
            temp = temp->next;
        }
    }
};

int main() {
    PatientLinkedList list;

    list.add("Иванов Иван", 30, "Петров", "01.03.2026");
    list.add("Сидоров Алексей", 45, "Смирнова", "02.03.2026");
    list.add("Кузнецова Мария", 28, "Петров", "01.03.2026");

    cout << "Все записи:\n";
    list.printForward();

    cout << "\nПоиск по имени:\n";
    list.searchByName("Иванов Иван");

    cout << "\nПоиск по врачу:\n";
    list.searchByDoctor("Петров");

    cout << "\nПоиск по дате:\n";
    list.searchByDate("01.03.2026");

    cout << "\nИзменение врача для Иванов Иван:\n";
    list.changeDoctor("Иванов Иван", "Орлов");

    cout << "\nОтмена записи Сидоров Алексей:\n";
    list.remove("Сидоров Алексей");

    cout << "\nИтоговый список:\n";
    list.printForward();

    return 0;
}
