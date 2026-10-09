#include <iostream>
#include <cmath>
using namespace std;
int main() {
    setlocale(LC_ALL, "RU");
    double x;
    cout << "Введите число: ";
    cin >> x;

    // Проверка корректности ввода.
    if (cin.fail()) {
        cout << "Ошибка: введите число!\n";
        return 1;
    }

    if (x > 0) {
        cout << "Квадратный корень: " << sqrt(x) << '\n';
    } else {
        cout << "Квадрат числа: " << x * x << '\n';
    }
    return 0;
}
