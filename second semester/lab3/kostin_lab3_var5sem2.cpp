#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <random>
using namespace std;
using namespace std::chrono;

struct Employee {
    int id;
    string name;
    string position;
    string department;
    double salary;
    string hireDate;
};

size_t hashString(const string& str, size_t tableSize) {
    size_t hash = 0;
    for (char c : str) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

template<typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

template<typename K, typename V>
class Dictionary {
private:
    BSTNode<K, V>* root;
    
    void insert(BSTNode<K, V>*& node, K key, V value) {
        if (!node) {
            node = new BSTNode<K, V>(key, value);
            return;
        }
        if (key < node->key) {
            insert(node->left, key, value);
        } else if (key > node->key) {
            insert(node->right, key, value);
        } else {
            node->value = value;
        }
    }
    
    V* search(BSTNode<K, V>* node, K key) {
        if (!node) return nullptr;
        if (key < node->key) return search(node->left, key);
        if (key > node->key) return search(node->right, key);
        return &node->value;
    }
    
public:
    Dictionary() : root(nullptr) {}
    
    void insert(K key, V value) {
        insert(root, key, value);
    }
    
    V* search(K key) {
        return search(root, key);
    }
};

template<typename K, typename V>
class HashTable {
private:
    vector<vector<pair<K, V>>> table;
    size_t size;
    
public:
    HashTable(size_t s) : size(s), table(s) {}
    
    void insert(K key, V value) {
        size_t index = hashString(key, size);
        for (auto& p : table[index]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }
    
    V* search(K key) {
        size_t index = hashString(key, size);
        for (auto& p : table[index]) {
            if (p.first == key) {
                return &p.second;
            }
        }
        return nullptr;
    }
};

template<typename K>
class Dictionary2 {
private:
    BSTNode<K, vector<Employee>>* root;
    
    void insert(BSTNode<K, vector<Employee>>*& node, K key, Employee value) {
        if (!node) {
            node = new BSTNode<K, vector<Employee>>(key, {value});
            return;
        }
        if (key < node->key) {
            insert(node->left, key, value);
        } else if (key > node->key) {
            insert(node->right, key, value);
        } else {
            node->value.push_back(value);
        }
    }
    
    vector<Employee>* search(BSTNode<K, vector<Employee>>* node, K key) {
        if (!node) return nullptr;
        if (key < node->key) return search(node->left, key);
        if (key > node->key) return search(node->right, key);
        return &node->value;
    }
    
public:
    Dictionary2() : root(nullptr) {}
    
    void insert(K key, Employee value) {
        insert(root, key, value);
    }
    
    vector<Employee>* search(K key) {
        return search(root, key);
    }
};

template<typename K>
class HashTable2 {
private:
    vector<vector<pair<K, vector<Employee>>>> table;
    size_t size;
    
public:
    HashTable2(size_t s) : size(s), table(s) {}
    
    void insert(K key, Employee value) {
        size_t index = hashString(key, size);
        for (auto& p : table[index]) {
            if (p.first == key) {
                p.second.push_back(value);
                return;
            }
        }
        table[index].push_back({key, {value}});
    }
    
    vector<Employee>* search(K key) {
        size_t index = hashString(key, size);
        for (auto& p : table[index]) {
            if (p.first == key) {
                return &p.second;
            }
        }
        return nullptr;
    }
};

vector<Employee> generateEmployees(int count) {
    vector<Employee> employees;
    
    vector<string> names = {"Иван", "Петр", "Сергей", "Дмитрий", "Александр", "Франк", "Ильяз", "Геннадий", "Константин", "Юрий"};
    vector<string> secondname = {"Иванович", "Петрович", "Сергеевич", "Дмитриевич", "Николаевич", "Франкович", "Евгеньевич", "Геннадиевич", "Юрьевич"};
    vector<string> surnames = {"Клинкман", "Сурков", "Петушков", "Швабрин", "Джариев", "Франков", "Андреев", "Петров", "Юрьев"};
    vector<string> positions = {"Менеджер", "Разработчик", "Дизайнер", "Аналитик", "Инженер", "Консультант", "Специалист"};
    vector<string> departments = {"HR", "IT", "Финансы", "Маркетинг", "Продажи"};
    vector<string> hireDates = {"01-01-2020", "15-02-2021", "20-03-2022", "10-05-2019", "05-07-2023"};

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> nameDist(0, names.size() - 1);
    uniform_int_distribution<> patDist(0, secondname.size() - 1);
    uniform_int_distribution<> surDist(0, surnames.size() - 1);
    uniform_int_distribution<> posDist(0, positions.size() - 1);
    uniform_int_distribution<> deptDist(0, departments.size() - 1);
    uniform_int_distribution<> dateDist(0, hireDates.size() - 1);
    uniform_real_distribution<> salDist(30000, 100000);

    for (int i = 0; i < count; ++i) {
        Employee e;
        e.id = i + 1;
        e.name = names[nameDist(gen)] + " " + secondname[patDist(gen)] + " " + surnames[surDist(gen)];
        e.position = positions[posDist(gen)];
        e.department = departments[deptDist(gen)];
        e.salary = salDist(gen);
        e.hireDate = hireDates[dateDist(gen)];
        employees.push_back(e);
    }
    
    return employees;
}

int main() {
    const int NUM_EMPLOYEES = 30;
    vector<Employee> employees = generateEmployees(NUM_EMPLOYEES);

    // ============== ЗАДАЧА 1: ПОИСК ПО ФИО ==============
    Dictionary<string, Employee> dict1;
    HashTable<string, Employee> ht1(200);

    for (const auto& e : employees) {
        dict1.insert(e.name, e);
        ht1.insert(e.name, e);
    }

    string searchName = employees[29].name;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = dict1.search(searchName);
    }
    auto end = high_resolution_clock::now();
    auto dictTime1 = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = ht1.search(searchName);
    }
    end = high_resolution_clock::now();
    auto htTime1 = duration_cast<microseconds>(end - start).count();

    cout << "\n=== ЗАДАЧА 1: Поиск сотрудника по ФИО ===" << endl;
    cout << "Поиск: " << searchName << endl;
    cout << "Время словаря: " << dictTime1 << " мкс" << endl;
    cout << "Время хеш-таблицы:   " << htTime1 << " мкс" << endl;
    cout << "Результат: " << (dictTime1 < htTime1 ? "Словарь быстрее" : "Хеш-таблица быстрее") << endl;

    // ============== ЗАДАЧА 2: СПИСОК СОТРУДНИКОВ ОТДЕЛА ==============
    Dictionary2<string> dict2;
    HashTable2<string> ht2(200);

    for (const auto& e : employees) {
        dict2.insert(e.department, e);
        ht2.insert(e.department, e);
    }

    string searchDept = employees[0].department;

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = dict2.search(searchDept);
    }
    end = high_resolution_clock::now();
    auto dictTime2 = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto res = ht2.search(searchDept);
    }
    end = high_resolution_clock::now();
    auto htTime2 = duration_cast<microseconds>(end - start).count();

    cout << "\n=== ЗАДАЧА 2: Список сотрудников отдела ===" << endl;
    cout << "Поиск по отделу: " << searchDept << endl;
    
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
    
    cout << "Время словаря: " << dictTime2 << " мкс" << endl;
    cout << "Время хеш-таблицы:   " << htTime2 << " мкс" << endl;
    cout << "Результат: " << (dictTime2 < htTime2 ? "Словарь быстрее" : "Хеш-таблица быстрее") << endl;

    return 0;
}

