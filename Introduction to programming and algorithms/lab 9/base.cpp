// Функция: double average(double a, double b)
// Задание: вычислить среднее арифметическое двух чисел.
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Прототипы функций
double average(double a, double b);
double readDouble(const string& pr);

int main() {
    double first = readDouble("Введите первое число: ");
    double second = readDouble("Введите второе число: ");

    // Вызов функции и использование возвращаемого значения
    double result = average(first, second);

    cout << fixed << setprecision(2);
    cout << "Среднее арифметическое " << first << " и " << second << " = "
              << result << endl;

    return 0;
}

// Вычисляет среднее арифметическое двух чисел.
// Параметры: a, b - исходные числа.
// Возвращает: (a + b) / 2.
double average(double a, double b) {
    return (a + b) / 2.0;
}

// Читает вещественное число с клавиатуры; при ошибке ввода повторяет запрос.
// Параметры: pr - приглашение к вводу.
// Возвращает: введённое число.
double readDouble(const string& pr) {
    double value;
    while (true) {
        cout << pr;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Ошибка: нужно ввести число!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
