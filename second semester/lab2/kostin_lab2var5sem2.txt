#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <iomanip>
using namespace std;
 
struct Request {
    int id;
    time_t arrival;
    string type;
    double mass;
    size_t prio;
};
struct PriorityQueueNode {
    Request req;
    PriorityQueueNode* next;
    PriorityQueueNode* prev;
    PriorityQueueNode(const Request& r) {
        this->req = r;
        this->prev = nullptr;
        this->next = nullptr;
    }
};
class PriorityQueue {
private:
    PriorityQueueNode* front;
    PriorityQueueNode* tail;
    size_t count;
public:
    PriorityQueue() {
        this->front=nullptr;
        this->tail=nullptr;
        this->count=0;
    }
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
    void enqueue(Request r) {
        PriorityQueueNode* newNode = new PriorityQueueNode(r);
        
        if (!tail) {
            front = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
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
            if (cur->req.prio > best->req.prio) {
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
    Request pop() {
        if (!front) {
            throw runtime_error("Очередь пуста: pop невозможен");
        }
        // Найти узел с максимальным приоритетом
        PriorityQueueNode* best = front;
        for (PriorityQueueNode* cur = front->next; cur != nullptr; cur = cur->next) {
            if (cur->req.prio > best->req.prio) {
                best = cur;
            }
        }
        // Сохранить значение
        Request result = best->req;
        // Изъятие best из двусвязного списка
        if (best->prev) best->prev->next = best->next;
        else front = best->next;
        if (best->next) best->next->prev = best->prev;
        else tail = best->prev;
        delete best;
        --count;
        return result;
    }

    bool empty() const { return count == 0; }
    size_t size() const { return count; }

    // Печать очереди
    void print() {
        cout << "[size=" << count << "] ";
        for (PriorityQueueNode* cur = front; cur != nullptr; cur = cur->next) {
            cout << "{val: " << cur->req.id << ", prio: " << cur->req.prio << "}";
            if (cur->next)
                cout << " <- ";
        }
        cout << endl;
    }
};

// Вспомогательная функция для создания времени
time_t createTime(int year, int month, int day, int hour, int min) {
    struct tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month -1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = 0;
    return mktime(&t);
};
int getPrio(const Request& r) {
    int p = (r.type == "package") ? 20 : 10;
    if (r.mass > 10.0) p += 10;
    else if (r.mass > 5.0) p += 5;
    return p;
};

    
int main() {
    PriorityQueue pq;
    const int N = 10;
    Request arrivals[N] = {
        {1, createTime(2026, 4, 9, 10, 0), "letter", 0.5, 0},
        {2, createTime(2026, 4, 9, 10, 2), "package", 3.0, 0},
        {3, createTime(2026, 4, 9, 10, 5), "letter", 0.2, 0},
        {4, createTime(2026, 4, 9, 10, 6), "package", 7.5, 0},
        {5, createTime(2026, 4, 9, 10, 9), "package", 1.0, 0},
        {6, createTime(2026, 4, 9, 10, 10), "letter", 0.8, 0},
        {7, createTime(2026, 4, 9, 10, 15), "package", 5.0, 0},
        {8, createTime(2026, 4, 9, 10, 16), "letter", 0.3, 0},
        {9, createTime(2026, 4, 9, 10, 17), "package", 11.0, 0},
        {10, createTime(2026, 4, 9, 10, 30), "letter", 0.1, 0}
    };
    for (int i = 0; i < N; ++i) {
        arrivals[i].prio = getPrio(arrivals[i]);
    }

    double totalWait = 0, totalProc = 0;
    time_t currentTime = arrivals[0].arrival;
    int nextArrivalIndex = 0;

    cout << "Почтовое отделение:\n";
    while (nextArrivalIndex < N || !pq.empty()) {
        if (pq.empty()) {
            currentTime = max(currentTime, arrivals[nextArrivalIndex].arrival);
        }

        while (nextArrivalIndex < N && arrivals[nextArrivalIndex].arrival <= currentTime) {
            const Request& req = arrivals[nextArrivalIndex];
            pq.enqueue(req);
            cout << "\nЗаявка " << req.id
                 << ", тип: " << req.type
                 << ", масса: " << req.mass << " кг, "
                 << "приоритет: " << req.prio << endl;
            // cout << "Очередь: ";
            // pq.print();
            ++nextArrivalIndex;
        }

        if (!pq.empty()) {
            Request next = pq.pop();
            double wait = 0.0;
            if (currentTime > next.arrival) {
                wait = difftime(currentTime, next.arrival) / 60.0;
            }
            int proc = (next.type == "package") ? 8 : 2;
            totalWait += wait;
            totalProc += proc;
            currentTime += proc * 60;
            cout << "ОБСЛУЖЕНА " << next.id
                 << ", ожидание: " << fixed << setprecision(1) << wait << " мин"
                 << ", обработка: " << proc << " мин" << endl;
        }
    }

    double totalTime = difftime(currentTime, arrivals[0].arrival) / 60.0;
    cout << "\nСтатистика: " << endl;
    cout << "Загрузка отделения: " << fixed << setprecision(2) << (totalProc / totalTime) * 100 << " %" << endl;
    cout << "Среднее ожидание:   " << fixed << setprecision(2) << totalWait / N << " мин" << endl;
    cout << "Средняя обработка:  " << fixed << setprecision(2) << totalProc / N << " мин" << endl;
    cout << "Общее время модели: " << fixed << setprecision(2) << totalTime << " мин" << endl;

    return 0;
};