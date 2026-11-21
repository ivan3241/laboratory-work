// Функция: void setMin(int& a, int b)
// Задание: записать минимум из двух чисел в первую переменную.
//
// a передаётся ПО ССЫЛКЕ  - функция меняет исходную переменную;
// b передаётся ПО ЗНАЧЕНИЮ - функция работает с копией, b не меняется.
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Прототипы функций
void setMin(int& a, int b);
int readInt(const string& pr);

int main() {
    int first = readInt("Введите первое число (a): ");
    int second = readInt("Введите второе число (b): ");

    cout << "\nДо вызова:    a = " << first << ", b = " << second << endl;

    setMin(first, second);  // first изменится, second останется прежним

    cout << "После вызова: a = " << first << ", b = " << second << endl;
    cout << "В переменной a теперь минимум из двух чисел." << endl;

    return 0;
}

// Записывает минимум из a и b в переменную a.
// Параметры: a - ссылка на изменяемую переменную (на выходе - минимум);
//            b - второе число, передаётся по значению (не изменяется).
// Возвращает: ничего (результат записывается в a).
void setMin(int& a, int b) {
    if (b < a) {
        a = b;  // меняем исходную переменную вызывающей функции
    }
}

// Читает целое число; при ошибке ввода повторяет запрос.
// Параметры: pr - приглашение к вводу.
// Возвращает: введённое число.
int readInt(const string& pr) {
    int value;
    while (true) {
        cout << pr;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Ошибка: нужно ввести целое число!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
