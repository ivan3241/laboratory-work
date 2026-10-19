#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    double total = 0.0;
    int choice = -1;

    while (choice != 0) {
        cout << "\n=== МАГАЗИН ===" << endl;
        cout << "1. Ноутбуки\n2. Смартфоны\n3. Оформить заказ и чек\n0. Выход" << endl;
        cout << "В корзине на сумму: " << fixed << setprecision(2) << total << " руб." << endl;
        cout << "Выберите пункт: ";

        // Проверка на корректность ввода числа
        if (!(cin >> choice)) {
            cout << "Ошибка: введите число!" << endl;
            cin.clear();
            while (cin.get() != '\n'); // компактная очистка буфера
            continue;
        }

        // Внешний switch: выбор категории или действия
        switch (choice) {
            case 1: { // Категория 1: Ноутбуки
                cout << "\n1. Игровой ноутбук (80 000 руб.)\n2. Офисный ноутбук (40 000 руб.)\nТовар: ";
                int item;
                if (cin >> item) {
                    // Вложенный switch: выбор товара в категории
                    switch (item) {
                        case 1: total += 80000; cout << "-> Добавлен игровой ноутбук." << endl; break;
                        case 2: total += 40000; cout << "-> Добавлен офисный ноутбук." << endl; break;
                        default: cout << "-> Неверный номер товара!" << endl; break;
                    }
                }
                break;
            }
            case 2: { // Категория 2: Смартфоны
                cout << "\n1. Флагман (60 000 руб.)\n2. Бюджетный (20 000 руб.)\nТовар: ";
                int item;
                if (cin >> item) {
                    // Вложенный switch: выбор товара в категории
                    switch (item) {
                        case 1: total += 60000; cout << "-> Добавлен флагман." << endl; break;
                        case 2: total += 20000; cout << "-> Добавлен бюджетный смартфон." << endl; break;
                        default: cout << "-> Неверный номер товара!" << endl; break;
                    }
                }
                break;
            }
            case 3: { // Оформление заказа и скидка
                if (total <= 0) {
                    cout << "Корзина пуста! Сначала выберите товары." << endl;
                    break;
                }
                cout << "\nСкидка: 1 - Без скидки, 2 - Студенческий (5%), 3 - VIP (10%)\nВыбор: ";
                int disc;
                double rate = 0.0;
                if (cin >> disc) {
                    // Switch для выбора скидки
                    switch (disc) {
                        case 1: rate = 0.00; break;
                        case 2: rate = 0.05; break;
                        case 3: rate = 0.10; break;
                        default: cout << "Неверный выбор, скидка 0%." << endl; break;
                    }
                }
                double discountSum = total * rate;
                cout << "\n============== ЧЕК ==============" << endl;
                cout << "Сумма без скидки: " << total << " руб." << endl;
                cout << "Скидка:          -" << discountSum << " руб." << endl;
                cout << "ИТОГО К ОПЛАТЕ:   " << (total - discountSum) << " руб." << endl;
                cout << "=================================" << endl;

                total = 0; // Очищаем корзину после оплаты
                break;
            }
            case 0:
                cout << "Завершение программы. " << endl;
                break;
            default:
                cout << "Ошибка: неверный пункт меню!" << endl;
                break;
        }
    }

    return 0;
}