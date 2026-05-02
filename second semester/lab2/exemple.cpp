#include <iostream>
using namespace std;
 
struct PriorityQueueNode {
    int data;            // Полезные данные
    size_t priority;     // Приоритет (больше = выше приоритет)
    PriorityQueueNode* prev;          // Указатель на предыдущий узел
    PriorityQueueNode* next;          // Указатель на следующий узел
    PriorityQueueNode(int value, size_t prio) {
        this->data=value;
        this->priority=prio;
        this->prev=nullptr;
        this->next=nullptr;
    }
};
class PriorityQueue {
private:
    PriorityQueueNode* front;  // Голова списка (наивысший приоритет)
    PriorityQueueNode* tail;   // Хвост списка (наименьший приоритет)
    size_t count; // Текущий размер
public:
    //Конструктор, инициализация пустого списка
    PriorityQueue() {
        this->front=nullptr;
        this->tail=nullptr;
        this->count=0;
    }
    // Деструктор (освобождение памяти)
    ~PriorityQueue() {
        PriorityQueueNode* temp = front;
        while (temp != nullptr) {
            PriorityQueueNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        front = tail = nullptr;
        count = 0;
    }
    // Добавление в конец (enqueue)
    void enqueue(int value, size_t prio) {
        PriorityQueueNode* newPriorityQueueNode = new PriorityQueueNode(value, prio);
        if (!tail) {
            // Очередь пуста
            front = tail = newPriorityQueueNode;
        } else {
            newPriorityQueueNode->prev = tail;
            tail->next = newPriorityQueueNode;
            tail = newPriorityQueueNode;
        }
        ++count;
    }
    
    // Извлечь значение элемента с максимальным приоритетом
    // Больше — значит лучше (максимальный приоритет лучший)
    void dequeue() {
        if (!front) {
            throw runtime_error("Очередь пуста: dequeue невозможен");
        }
        PriorityQueueNode* best = front;
        for (PriorityQueueNode* cur = front->next; cur != nullptr; cur = cur->next) {
            if (cur->priority > best->priority) {
                best = cur;
            }
        }
        if (best->prev) best->prev->next = best->next;
        else front = best->next;
        if (best->next) best->next->prev = best->prev;
        else tail = best->prev;
        delete best;
        --count;
    }
    // Извлечь и вернуть значение элемента с максимальным приоритетом
    // Больше — значит лучше (максимальный приоритет лучший)
    int pop() {
        if (!front) {
            throw runtime_error("Очередь пуста: pop невозможен");
        }
        // Найти узел с максимальным приоритетом
        PriorityQueueNode* best = front;
        for (PriorityQueueNode* cur = front->next; cur != nullptr; cur = cur->next) {
            if (cur->priority > best->priority) {
                best = cur;
            }
        }
        // Сохранить значение
        int result = best->data;
        // Изъятие best из двусвязного списка
        if (best->prev) best->prev->next = best->next;
        else front = best->next;
        if (best->next) best->next->prev = best->prev;
        else tail = best->prev;
 
        delete best;
        --count;
        return result;
    }
    
    // Печать очереди
    void print() {
        cout << "[size=" << count << "] ";
        for (PriorityQueueNode* cur = front; cur != nullptr; cur = cur->next) {
            cout << "{val: " << cur->data << ", prio: " << cur->priority << "}";
            if (cur->next)
                cout << " <- ";
        }
        cout << endl;
    }
};
 
int main()
{
    PriorityQueue q;
    q.enqueue(10,1);
    q.enqueue(20,3);
    q.enqueue(30,1);
    q.enqueue(40,2);
    q.print();
    q.dequeue();
    q.print();
    // Пример работы pop
    int top1 = q.pop();
    cout << "pop -> " << top1 << endl;
    q.print();
    return 0;
}
