#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
const double PI = 3.1415; // Константа числа Пи
double radius;
double height;
cout << "Введите радиус основания цилиндра: ";
if (!(cin >> radius)) {
    cout << "Ошибка: введено не число" << endl;
    return 1;
}
cout << "Введите высоту цилиндра: ";
if (!(cin >> height)) {
    cout << "Ошибка: введено не число" << endl;
    return 1;
}
if (radius <0 || height < 0) {
    cout << "Ошибка: радиус и высота не могут быть отрицательными" << endl;
    return 1;
}
double f = PI * static_cast<double>(radius * radius) * height; // Вычисление объема цилиндра

cout << fixed << setprecision(4);
cout << "Объем цилиндра: " << f << endl;

    return 0;
}