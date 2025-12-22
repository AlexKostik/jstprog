#include <iostream>
#include <string>
using namespace std;

class Car {
protected:
    string brand;
    string model;
    int year;

public:
    Car(string b, string m, int y) : brand(b), model(m), year(y) {}

    // Метод для вывода информации о машине (не изменяемый)
    void showInfo() {
        cout << "Марка: " << brand << ", Модель: " << model << ", Год: " << year << endl;
    }

    // Метод для изменения года выпуска (не изменяемый)
    void setYear(int y) {
        if (y > 1900 && y <= 2025)
            year = y;
        else
            cout << "Некорректный год!" << endl;
    }

    // Метод для изменения модели (может наследоваться и переопределяться)
    virtual void setModel(string m) {
        model = m;
    }

    // Метод для вывода модели (может наследоваться и переопределяться)
    virtual void showModel() {
        cout << "Модель: " << model << endl;
    }
};

// Производный класс
class ServiceCar : public Car {
private:
    string serviceStatus; // статус обслуживания
public:
    ServiceCar(string b, string m, int y, string status)
        : Car(b, m, y), serviceStatus(status) {}

    // Переопределяем метод показа модели
    void showModel() override {
        cout << "Модель машины на сервисе: " << model << " (статус: " << serviceStatus << ")" << endl;
    }

    // Метод только для ServiceCar
    void setServiceStatus(string status) {
        serviceStatus = status;
    }

    void showServiceStatus() {
        cout << "Статус обслуживания: " << serviceStatus << endl;
    }
};

int main() {
    Car car1("Subaru", "Impreza", 2005);
    car1.showInfo();
    car1.showModel();
    car1.setModel("Legacy");
    car1.showModel();

    cout << endl;

    ServiceCar serviceCar1("Toyota", "Camry", 2010, "В работе");
    serviceCar1.showInfo();        // наследуемый метод
    serviceCar1.showModel();       // переопределенный метод
    serviceCar1.setServiceStatus("Готово");
    serviceCar1.showServiceStatus();

    return 0;
}