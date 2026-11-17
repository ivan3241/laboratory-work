// Решение квадратного уравнения a*x^2 + b*x + c = 0.
// Главная функция: int solveQuadratic(double a, double b, double c, double& x1, double& x2)
// Возвращает количество корней, а сами корни — через ссылки.
// Декомпозиция: каждая функция выполняет одну задачу.
//readDouble          - безопасный ввод числа
//readCoefficients    - ввод a, b, c
//calculateDiscriminant - вычисление дискриминанта
//solveQuadratic      - решение уравнения
//printEquation       - вывод уравнения
//printRoots          - вывод результата
//runSolver           - один сеанс: ввод -> решение -> вывод
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

const double EPSILON = 1e-9;          // допуск при сравнении с нулём
const int INFINITE_ROOTS = -1;        // код результата: бесконечно много корней
const int PRECISION = 4;              // знаков после запятой при выводе

// ---------- Прототипы функций ----------
double readDouble(const string& pr);
void readCoefficients(double& a, double& b, double& c);
double calculateDiscriminant(double a, double b, double c);
int solveQuadratic(double a, double b, double c, double& x1, double& x2);
void printEquation(double a, double b, double c);
void printRoots(int rootsCount, double x1, double x2);
void runSolver();

int main() {
    cout << fixed << setprecision(PRECISION);

    bool again = true;
    while (again) {
        runSolver();

        cout << "\nРешить ещё одно уравнение? (1 - да, 0 - нет): ";
        int answer;
        if (!(cin >> answer)) {
            break;  // конец ввода или ошибка — завершаем
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        again = (answer == 1);
        cout << endl;
    }

    return 0;
}

//Определения функций

// Читает вещественное число; при ошибке ввода повторяет запрос.
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
        if (cin.eof()) {
            cout << "\nВвод прерван." << endl;
            exit(0);
        }
        cout << "Ошибка: нужно ввести число!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Вводит коэффициенты уравнения a*x^2 + b*x + c = 0.
// Параметры (по ссылке, на выходе): a, b, c - коэффициенты.
// Возвращает: ничего (результат записывается в параметры).
void readCoefficients(double& a, double& b, double& c) {
    a = readDouble("Введите a: ");
    b = readDouble("Введите b: ");
    c = readDouble("Введите c: ");
}

// Вычисляет дискриминант D = b^2 - 4ac.
// Параметры: a, b, c - коэффициенты уравнения.
// Возвращает: значение дискриминанта.
double calculateDiscriminant(double a, double b, double c) {
    return b * b - 4.0 * a * c;
}

// Решает уравнение a*x^2 + b*x + c = 0 (в том числе вырожденные случаи).
// Параметры: a, b, c - коэффициенты;
//            x1, x2 - (по ссылке) сюда записываются найденные корни.
// Возвращает: количество корней (0, 1 или 2) либо INFINITE_ROOTS (-1),
//             если уравнение имеет бесконечно много решений (a = b = c = 0).
//             Если корень один, он записывается в x1 (x2 = x1).
int solveQuadratic(double a, double b, double c, double& x1, double& x2) {
    x1 = 0.0;
    x2 = 0.0;

    // Вырожденный случай: a = 0, уравнение линейное b*x + c = 0
    if (fabs(a) < EPSILON) {
        if (fabs(b) < EPSILON) {
            // 0*x + c = 0: верно при любом x, если c = 0, иначе решений нет
            return (fabs(c) < EPSILON) ? INFINITE_ROOTS : 0;
        }
        x1 = -c / b;
        x2 = x1;
        return 1;
    }

    double discriminant = calculateDiscriminant(a, b, c);

    if (discriminant < -EPSILON) {
        return 0;  // D < 0 — действительных корней нет
    }
    if (fabs(discriminant) <= EPSILON) {
        x1 = -b / (2.0 * a);  // D = 0 — один (кратный) корень
        x2 = x1;
        return 1;
    }

    double sqrtD = sqrt(discriminant);  // D > 0 — два корня
    x1 = (-b - sqrtD) / (2.0 * a);
    x2 = (-b + sqrtD) / (2.0 * a);
    return 2;
}

// Выводит уравнение в виде строки.
// Параметры: a, b, c - коэффициенты.
// Возвращает: ничего.
void printEquation(double a, double b, double c) {
    cout << "Уравнение: (" << a << ")x^2 + (" << b << ")x + (" << c
              << ") = 0" << endl;
}

// Выводит результат решения.
// Параметры: rootsCount - значение, возвращённое solveQuadratic;
//            x1, x2 - корни.
// Возвращает: ничего.
void printRoots(int rootsCount, double x1, double x2) {
    switch (rootsCount) {
        case INFINITE_ROOTS:
            cout << "Решений бесконечно много (любое x)." << endl;
            break;
        case 0:
            cout << "Действительных корней нет." << endl;
            break;
        case 1:
            cout << "Один корень: x = " << x1 << endl;
            break;
        default:
            cout << "Два корня: x1 = " << x1 << ", x2 = " << x2 << endl;
            break;
    }
}

// Один сеанс работы: ввод коэффициентов, решение и вывод результата.
// Параметры: нет.
// Возвращает: ничего.
void runSolver() {
    double a, b, c;
    double x1, x2;

    readCoefficients(a, b, c);
    cout << endl;
    printEquation(a, b, c);

    int rootsCount = solveQuadratic(a, b, c, x1, x2);
    printRoots(rootsCount, x1, x2);
}
