#include <iostream>     // Для вывода результатов
#include <string>       // Для работы со строками
#include <chrono>       // Для измерения времени выполнения
#include <vector>       // Для динамических массивов
#include <random>       // Для генерации случайных данных
using namespace std;
using namespace std::chrono;

// Структура для представления сотрудника
struct Employee {
    int id;                // Уникальный идентификатор сотрудника
    string name;           // Полное имя сотрудника
    string position;       // Должность
    string department;     // Отдел, в котором работает сотрудник
    double salary;         // Зарплата
    string hireDate;       // Дата приема на работу
};

// Функция хеширования для строк (полиномиальный хеш с основанием 31)
size_t hashString(const string& str, size_t tableSize) {
    size_t hash = 0;
    // Проходим по каждому символу строки
    for (char c : str) {
        // Вычисляем хеш: (hash * 31 + ASCII_код) % размер_таблицы
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;  // Возвращаем индекс в таблице
}

// Узел бинарного дерева поиска для реализации словаря
template<typename K, typename V>
struct BSTNode {
    K key;              // Ключ (строка для поиска)
    V value;            // Значение (данные сотрудника или лист сотрудников)
    BSTNode* left;      // Указатель на левого потомка
    BSTNode* right;     // Указатель на правого потомка
    
    // Конструктор узла
    BSTNode(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Класс словаря, реализованный на основе бинарного дерева поиска
// Обеспечивает упорядоченые доступ к элементам
template<typename K, typename V>
class Dictionary {
private:
    BSTNode<K, V>* root;  // Корень дерева
    
    // Рекурсивная вставка элемента в дерево
    void insert(BSTNode<K, V>*& node, K key, V value) {
        if (!node) {
            // Если узел не существует, создаем новый
            node = new BSTNode<K, V>(key, value);
            return;
        }
        if (key < node->key) {
            // Ключ меньше - идем влево
            insert(node->left, key, value);
        } else if (key > node->key) {
            // Ключ больше - идем вправо
            insert(node->right, key, value);
        } else {
            // Ключ найден - обновляем значение
            node->value = value;
        }
    }
    
    // Рекурсивный поиск элемента в дереве
    V* search(BSTNode<K, V>* node, K key) {
        if (!node) return nullptr;  // Узел не найден
        if (key < node->key) return search(node->left, key);    // Ищем слева
        if (key > node->key) return search(node->right, key);   // Ищем справа
        return &node->value;  // Узел найден, возвращаем указатель
    }
    
public:
    Dictionary() : root(nullptr) {}  // Конструктор - инициализируем пустое дерево
    
    // Вставить элемент в словарь
    void insert(K key, V value) {
        insert(root, key, value);
    }
    
    // Поиск элемента по ключу
    V* search(K key) {
        return search(root, key);
    }
};

// Класс хеш-таблицы с методом цепочек для разрешения коллизий
// Обеспечивает быстрый поиск в среднем случае O(1)
template<typename K, typename V>
class HashTable {
private:
    vector<vector<pair<K, V>>> table;  // Таблица: вектор цепочек (векторов пар ключ-значение)
    size_t size;                       // Размер таблицы
    
public:
    // Конструктор: инициализируем таблицу размером s
    HashTable(size_t s) : size(s), table(s) {}
    
    // Вставить элемент в хеш-таблицу
    void insert(K key, V value) {
        // Вычисляем индекс в таблице с помощью хеш-функции
        size_t index = hashString(key, size);
        
        // Проверяем, существует ли уже такой ключ в цепочке
        for (auto& p : table[index]) {
            if (p.first == key) {
                // Ключ найден - обновляем значение
                p.second = value;
                return;
            }
        }
        
        // Ключ не найден - добавляем новую пару в цепочку
        table[index].push_back({key, value});
    }
    
    // Поиск элемента по ключу в хеш-таблице
    V* search(K key) {
        // Вычисляем индекс в таблице
        size_t index = hashString(key, size);
        
        // Ищем ключ в цепочке коллизий
        for (auto& p : table[index]) {
            if (p.first == key) {
                // Ключ найден - возвращаем указатель на значение
                return &p.second;
            }
        }
        
        // Ключ не найден
        return nullptr;
    }
};

// Неспециализированные классы для задачи 2
template<typename K>
class Dictionary2 {
private:
    BSTNode<K, vector<Employee>>* root;  // Корень дерева
    
    // Рекурсивная вставка: если ключ существует, добавляем сотрудника в список
    void insert(BSTNode<K, vector<Employee>>*& node, K key, Employee value) {
        if (!node) {
            // Создаем новый узел с пустым вектором и добавляем сотрудника
            node = new BSTNode<K, vector<Employee>>(key, {value});
            return;
        }
        if (key < node->key) {
            insert(node->left, key, value);
        } else if (key > node->key) {
            insert(node->right, key, value);
        } else {
            // Отдел найден - добавляем сотрудника в список
            node->value.push_back(value);
        }
    }
    
    // Рекурсивный поиск списка сотрудников по отделу
    vector<Employee>* search(BSTNode<K, vector<Employee>>* node, K key) {
        if (!node) return nullptr;
        if (key < node->key) return search(node->left, key);
        if (key > node->key) return search(node->right, key);
        return &node->value;  // Возвращаем вектор сотрудников в отделе
    }
    
public:
    Dictionary2() : root(nullptr) {}  // Конструктор
    
    // Добавить сотрудника в отдел
    void insert(K key, Employee value) {
        insert(root, key, value);
    }
    
    // Получить список сотрудников отдела
    vector<Employee>* search(K key) {
        return search(root, key);
    }
};

// Хеш-таблица для задачи 2
template<typename K>
class HashTable2 {
private:
    vector<vector<pair<K, vector<Employee>>>> table;  // Таблица: вектор цепочек
    size_t size;  // Размер таблицы
    
public:
    // Конструктор
    HashTable2(size_t s) : size(s), table(s) {}
    
    // Добавить сотрудника в отдел
    void insert(K key, Employee value) {
        // Вычисляем индекс по названию отдела
        size_t index = hashString(key, size);
        
        // Ищем отдел в цепочке коллизий
        for (auto& p : table[index]) {
            if (p.first == key) {
                // Отдел найден - добавляем сотрудника в список
                p.second.push_back(value);
                return;
            }
        }
        
        // Отдел не найден - создаем новую запись
        table[index].push_back({key, {value}});
    }
    
    // Получить список сотрудников отдела
    vector<Employee>* search(K key) {
        // Вычисляем индекс
        size_t index = hashString(key, size);
        
        // Ищем отдел в цепочке
        for (auto& p : table[index]) {
            if (p.first == key) {
                // Возвращаем вектор сотрудников в отделе
                return &p.second;
            }
        }
        
        return nullptr;  // Отдел не найден
    }
};

// Функция для генерации случайного набора сотрудников
// count - количество сотрудников для создания
vector<Employee> generateEmployees(int count) {
    vector<Employee> employees;  // Вектор для хранения сотрудников
    
    // Списки данных для генерации сотрудников
    vector<string> names = {"Иван", "Петр", "Сергей", "Дмитрий", "Александр", "Франк", "Ильяз", "Геннадий", "Константин", "Юрий"};
    vector<string> secondname = {"Иванович", "Петрович", "Сергеевич", "Дмитриевич", "Николаевич", "Франкович", "Евгеньевич", "Геннадиевич", "Юрьевич"};
    vector<string> surnames = {"Клинкман", "Сурков", "Петушков", "Швабрин", "Джариев", "Франков", "Андреев", "Петров", "Юрьев"};
    vector<string> positions = {"Менеджер", "Разработчик", "Дизайнер", "Аналитик", "Инженер", "Консультант", "Специалист"};
    vector<string> departments = {"HR", "IT", "Финансы", "Маркетинг", "Продажи"};
    vector<string> hireDates = {"01-01-2020", "15-02-2021", "20-03-2022", "10-05-2019", "05-07-2023"};
    
    // Инициализируем генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    
    // Распределения для выбора случайных элементов
    uniform_int_distribution<> nameDist(0, names.size() - 1);        // Для имен
    uniform_int_distribution<> patDist(0, secondname.size() - 1);   // Для отчеств
    uniform_int_distribution<> surDist(0, surnames.size() - 1);      // Для фамилий
    uniform_int_distribution<> posDist(0, positions.size() - 1);     // Для должностей
    uniform_int_distribution<> deptDist(0, departments.size() - 1);  // Для отделов
    uniform_int_distribution<> dateDist(0, hireDates.size() - 1);    // Для дат
    uniform_real_distribution<> salDist(30000, 100000);              // Для зарплат

    // Генерируем count сотрудников
    for (int i = 0; i < count; ++i) {
        Employee e;
        e.id = i + 1;  // ID от 1 до count
        
        // Генерируем полное ФИО: имя + отчество + фамилия
        e.name = names[nameDist(gen)] + " " + secondname[patDist(gen)] + " " + surnames[surDist(gen)];
        
        // Случайно выбираем должность, отдел и дату
        e.position = positions[posDist(gen)];
        e.department = departments[deptDist(gen)];
        e.salary = salDist(gen);
        e.hireDate = hireDates[dateDist(gen)];
        
        // Добавляем сотрудника в вектор
        employees.push_back(e);
    }
    
    return employees;
}

int main() {
    // Константа: количество сотрудников для теста
    const int NUM_EMPLOYEES = 30;
    
    // Генерируем 30 случайных сотрудников
    vector<Employee> employees = generateEmployees(NUM_EMPLOYEES);

    // ============== ЗАДАЧА 1: ПОИСК ПО ФИО ==============
    // Создаем словарь и хеш-таблицу для поиска по имени
    Dictionary<string, Employee> dict1;      // Бинарное дерево поиска
    HashTable<string, Employee> ht1(200);    // Хеш-таблица размером 200

    // Вставляем всех сотрудников в обе структуры данных
    for (const auto& e : employees) {
        dict1.insert(e.name, e);
        ht1.insert(e.name, e);
    }

    // Выбираем для поиска имя 50-го сотрудника
    string searchName = employees[50].name;  // Индексация с 0

    // Измеряем время поиска в СЛОВАРЕ (бинарное дерево)
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = dict1.search(searchName);  // 1000 поисков
    }
    auto end = high_resolution_clock::now();
    auto dictTime1 = duration_cast<microseconds>(end - start).count();

    // Измеряем время поиска в ХЕШ-ТАБЛИЦЕ
    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = ht1.search(searchName);  // 1000 поисков
    }
    end = high_resolution_clock::now();
    auto htTime1 = duration_cast<microseconds>(end - start).count();

    // Выводим результаты для задачи 1
    cout << "\n=== ЗАДАЧА 1: Поиск сотрудника по ФИО ===" << endl;
    cout << "Поиск: " << searchName << endl;
    cout << "Время словаря (BST): " << dictTime1 << " мкс" << endl;
    cout << "Время хеш-таблицы:   " << htTime1 << " мкс" << endl;
    cout << "Результат: " << (dictTime1 < htTime1 ? "Словарь быстрее" : "Хеш-таблица быстрее") << endl;

    // ============== ЗАДАЧА 2: СПИСОК СОТРУДНИКОВ ОТДЕЛА ==============
    // Создаем специальные структуры: ключ = отдел, значение = список сотрудников
    Dictionary2<string> dict2;  // Словарь для отделов (BST)
    HashTable2<string> ht2(200);  // Хеш-таблица для отделов

    // Вставляем всех сотрудников в обе структуры, группируя по отделам
    for (const auto& e : employees) {
        dict2.insert(e.department, e);    // Добавляем в словарь
        ht2.insert(e.department, e);      // Добавляем в хеш-таблицу
    }

    // Выбираем отдел первого сотрудника для поиска
    string searchDept = employees[0].department;

    // Измеряем время поиска всех сотрудников ОТДЕЛА в СЛОВАРЕ
    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = dict2.search(searchDept);  // Получаем вектор всех сотрудников отдела
    }
    end = high_resolution_clock::now();
    auto dictTime2 = duration_cast<microseconds>(end - start).count();

    // Измеряем время поиска всех сотрудников ОТДЕЛА в ХЕШ-ТАБЛИЦЕ
    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = ht2.search(searchDept);  // Получаем вектор всех сотрудников отдела
    }
    end = high_resolution_clock::now();
    auto htTime2 = duration_cast<microseconds>(end - start).count();

    // Выводим результаты для задачи 2
    cout << "\n=== ЗАДАЧА 2: Список сотрудников отдела ===" << endl;
    cout << "Поиск по отделу: " << searchDept << endl;
    
    // Получаем список сотрудников отдела для вывода
    auto deptEmployees = dict2.search(searchDept);
    if (deptEmployees && !deptEmployees->empty()) {
        cout << "Сотрудники в отделе: ";
        for (size_t i = 0; i < deptEmployees->size(); ++i) {
            cout << (*deptEmployees)[i].name;
            if (i < deptEmployees->size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Сотрудники в отделе: не найдены" << endl;
    }
    
    cout << "Время словаря (BST): " << dictTime2 << " мкс" << endl;
    cout << "Время хеш-таблицы:   " << htTime2 << " мкс" << endl;
    cout << "Результат: " << (dictTime2 < htTime2 ? "Словарь быстрее" : "Хеш-таблица быстрее") << endl;

    return 0;
}

