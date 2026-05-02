#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;

// Структура для хранения данных операции
struct Operation {
    int code;
    string name;
    string equipment;
    double time;
    double productivity;
};

// Узел бинарного дерева поиска
struct Node {
    Operation data;
    Node* left;
    Node* right;
};

// Создание нового узла дерева
Node* createNode(const Operation& op) {
    Node* node = new Node;
    node->data = op;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Вставка узла в дерево
Node* insertNode(Node* root, const Operation& op) {
    if (!root) {
        return createNode(op);
    }
    if (op.code < root->data.code) {
        root->left = insertNode(root->left, op);
    } else if (op.code > root->data.code) {
        root->right = insertNode(root->right, op);
    } else {
        root->data = op;
    }
    return root;
}

Node* searchNode(Node* root, int code) {
    if (!root || root->data.code == code) {
        return root;
    }
    if (code < root->data.code) {
        return searchNode(root->left, code);
    }
    return searchNode(root->right, code);
}

Node* findMin(Node* root) {
    if (!root) {
        return nullptr;
    }
    while (root->left) {
        root = root->left;
    }
    return root;
}

Node* findMax(Node* root) {
    if (!root) {
        return nullptr;
    }
    while (root->right) {
        root = root->right;
    }
    return root;
}

void printRecord(const Operation& op) {
    cout << "Код: " << op.code
              << ", Название: " << op.name
              << ", Оборудование: " << op.equipment
              << ", Время: " << op.time
              << ", Производительность: " << op.productivity
              << '\n';
}

void preorder(Node* root) {
    if (!root) {
        return;
    }
    printRecord(root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) {
        return;
    }
    inorder(root->left);
    printRecord(root->data);
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printRecord(root->data);
}

void levelOrder(Node* root) {
    if (!root) {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        printRecord(current->data);
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}

Node* deleteNode(Node* root, int code) {
    if (!root) {
        return nullptr;
    }
    if (code < root->data.code) {
        root->left = deleteNode(root->left, code);
    } else if (code > root->data.code) {
        root->right = deleteNode(root->right, code);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data.code);
    }
    return root;
}

bool equalTrees(Node* a, Node* b) {
    if (!a && !b) {
        return true;
    }
    if (!a || !b) {
        return false;
    }
    const Operation& oa = a->data;
    const Operation& ob = b->data;
    return oa.code == ob.code
        && oa.name == ob.name
        && oa.equipment == ob.equipment
        && oa.time == ob.time
        && oa.productivity == ob.productivity
        && equalTrees(a->left, b->left)
        && equalTrees(a->right, b->right);
}

int countLevelNodes(Node* root, int level) {
    if (!root || level < 0) {
        return 0;
    }
    if (level == 0) {
        return 1;
    }
    return countLevelNodes(root->left, level - 1)
         + countLevelNodes(root->right, level - 1);
}

Node* copyTree(Node* root) {
    if (!root) {
        return nullptr;
    }
    Node* copy = createNode(root->data);
    copy->left = copyTree(root->left);
    copy->right = copyTree(root->right);
    return copy;
}

void clearTree(Node* root) {
    if (!root) {
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}

Operation readOperation() {
    Operation op;
    cout << "Введите код операции: ";
    cin >> op.code;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите название: ";
    getline(cin, op.name);
    cout << "Введите тип оборудования: ";
    getline(cin, op.equipment);
    cout << "Введите время обработки: ";
    cin >> op.time;
    cout << "Введите производительность: ";
    cin >> op.productivity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op;
}

// Главная функция программы
int main() {
    Node* tree = nullptr;
    Node* copy = nullptr;
    while (true) {
        cout << "\nМеню:\n"
                  << "1. Добавить элемент\n"
                  << "2. Найти элемент\n"
                  << "3. Найти минимум\n"
                  << "4. Найти максимум\n"
                  << "5. Удалить элемент\n"
                  << "6. Прямой обход\n"
                  << "7. Симметричный обход\n"
                  << "8. Обратный обход\n"
                  << "9. Обход в ширину\n"
                  << "10. Подсчитать узлы на уровне\n"
                  << "11. Копировать дерево\n"
                  << "12. Сравнить дерево и копию\n"
                  << "0. Выход\n"
                  << "Выберите опцию: ";
        int choice;
        cin >> choice;
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1: {
                Operation op = readOperation();
                tree = insertNode(tree, op);
                break;
            }
            case 2: {
                cout << "Введите код для поиска: ";
                int code;
                cin >> code;
                Node* found = searchNode(tree, code);
                if (found) {
                    printRecord(found->data);
                } else {
                    cout << "Элемент не найден.\n";
                }
                break;
            }
            case 3: {
                Node* minNode = findMin(tree);
                if (minNode) {
                    printRecord(minNode->data);
                } else {
                    cout << "Дерево пустое.\n";
                }
                break;
            }
            case 4: {
                Node* maxNode = findMax(tree);
                if (maxNode) {
                    printRecord(maxNode->data);
                } else {
                    cout << "Дерево пустое.\n";
                }
                break;
            }
            case 5: {
                cout << "Введите код для удаления: ";
                int code;
                cin >> code;
                tree = deleteNode(tree, code);
                break;
            }
            case 6: {
                preorder(tree);
                break;
            }
            case 7: {
                inorder(tree);
                break;
            }
            case 8: {
                postorder(tree);
                break;
            }
            case 9: {
                levelOrder(tree);
                break;
            }
            case 10: {
                cout << "Введите уровень: ";
                int level;
                cin >> level;
                int count = countLevelNodes(tree, level);
                cout << "Узлов на уровне " << level << ": " << count << "\n";
                break;
            }
            case 11: {
                clearTree(copy);
                copy = copyTree(tree);
                cout << "Дерево скопировано.\n";
                break;
            }
            case 12: {
                if (equalTrees(tree, copy)) {
                    cout << "Деревья равны.\n";
                } else {
                    cout << "Деревья не равны.\n";
                }
                break;
            }
            default:
                cout << "Неверная опция.\n";
                break;
        }
    }
    clearTree(tree);
    clearTree(copy);
    return 0;
}
