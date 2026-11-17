// Функция: int lcm(int a, int b)
// Задание: вычислить НОК (наименьшее общее кратное) двух чисел.
// Формула: НОК(a, b) = a / НОД(a, b) * b
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Прототипы функций
int gcd(int a, int b);
int lcm(int a, int b);
int readPositiveInt(const string& pr);

int main() {
    int first = readPositiveInt("Введите первое натуральное число: ");
    int second = readPositiveInt("Введите второе натуральное число: ");

    int result = lcm(first, second);

    if (result == 0) {
        // lcm вернула 0 — значит, НОК не удалось вычислить
        cout << "НОК не вычислен: результат не помещается в int." << endl;
    } else {
        cout << "НОД(" << first << ", " << second << ") = "
                  << gcd(first, second) << endl;
        cout << "НОК(" << first << ", " << second << ") = " << result
                  << endl;
    }

    return 0;
}

// Вычисляет наибольший общий делитель по алгоритму Евклида.
// Параметры: a, b - неотрицательные целые числа.
// Возвращает: НОД(a, b); если оба числа равны 0, возвращает 0.
int gcd(int a, int b) {
    while (b != 0) {
        int remainder = a % b;  // остаток от деления
        a = b;
        b = remainder;
    }
    return a;
}

// Вычисляет наименьшее общее кратное двух чисел.
// Параметры: a, b - натуральные числа (> 0).
// Возвращает: НОК(a, b); 0, если a <= 0, b <= 0 или результат превышает INT_MAX.
int lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;  // граничный случай: НОК определён для натуральных чисел
    }
    // Сначала делим, потом умножаем — так промежуточное число меньше.
    // long long защищает от переполнения при умножении.
    long long product = static_cast<long long>(a / gcd(a, b)) * b;
    if (product > numeric_limits<int>::max()) {
        return 0;  // не помещается в int
    }
    return static_cast<int>(product);
}

// Читает натуральное число (> 0); при ошибке ввода повторяет запрос.
// Параметры: pr - приглашение к вводу.
// Возвращает: введённое натуральное число.
int readPositiveInt(const string& pr) {
    int value;
    while (true) {
        cout << pr;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value > 0) {
                return value;
            }
            cout << "Ошибка: число должно быть больше 0!" << endl;
        } else {
            cout << "Ошибка: нужно ввести целое число!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
