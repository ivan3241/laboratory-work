#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    const double EPSILON = 1e-9;
    double a, b, c;

    cout << "Введите три стороны: ";
    cin >> a >> b >> c;

    // Проверяем корректность ввода.
    if (cin.fail()) {
        cout << "Ошибка: необходимо ввести три числа.\n";
        return 1;
    }

    // Длины сторон должны быть положительными.
    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "Ошибка: стороны должны быть положительными.\n";
        return 1;
    }

    // Упорядочиваем стороны по возрастанию.
    double x = a, y = b, z = c;
    if (x > y) swap(x, y);
    if (y > z) swap(y, z);
    if (x > y) swap(x, y);

    // Проверяем существование треугольника.
    if (x + y <= z) {
        cout << "Треугольник не существует.\n";
        return 0;
    }

    // Сравниваем квадраты с заданной точностью.
    if (fabs(x*x + y*y - z*z) < EPSILON) {
        cout << "Прямоугольный треугольник.\n";
    } else {
        cout << "Не прямоугольный треугольник.\n";
    }
    return 0;
}
