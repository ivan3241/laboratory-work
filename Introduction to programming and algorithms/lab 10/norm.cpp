// Функция: void swapArithmetic(int& a, int& b)
// Задание: обменять значения двух целых чисел с помощью арифметики,
// без временной переменной.
//
// Идея: a = a + b;  b = a - b;  a = a - b;
//   после 1-го шага a = A + B
//   после 2-го шага b = (A + B) - B = A
//   после 3-го шага a = (A + B) - A = B
//   Дополнительно показано (требования среднего уровня):
//   - передача массива в функцию с изменением элементов (reverseArray);
//   - const T& для защиты от копирования и изменения (printLabel).
#include <iostream>
#include <limits>
#include <string>

const int ARRAY_SIZE = 5;

// Прототипы функций
void swapArithmetic(int& a, int& b);
void reverseArray(int arr[], int size);
void printArray(const int arr[], int size, const string& label);
int readInt(const string& pr);

int main() {
    //1. Обмен двух чисел
    int first = readInt("Введите первое число (a): ");
    int second = readInt("Введите второе число (b): ");

    cout << "\nДо обмена:    a = " << first << ", b = " << second << endl;
    swapArithmetic(first, second);
    cout << "После обмена: a = " << first << ", b = " << second << endl;

    //2. Граничный случай: обмен переменной с самой собой
    // Без проверки &a == &b результат был бы 0 (a - a), поэтому в функции есть защита.
    int same = 42;
    swapArithmetic(same, same);
    cout << "\nОбмен переменной с самой собой: same = " << same
              << " (значение сохранено)" << endl;

    //3. Массив: элементы меняются через ссылки 
    int numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    printArray(numbers, ARRAY_SIZE, "Массив до реверса");
    reverseArray(numbers, ARRAY_SIZE);
    printArray(numbers, ARRAY_SIZE, "Массив после реверса");

    return 0;
}

// Обменивает значения a и b без временной переменной (арифметический способ).
// Параметры: a, b - ссылки на обмениваемые переменные.
// Возвращает: ничего (меняются сами переменные вызывающей функции).
// Примечания:
//  1) Если a и b - одна и та же переменная, обмен не нужен: иначе a - a обнулит её.
//  2) Вычисления ведутся в unsigned int: переполнение беззнаковых чисел
//     определено стандартом (арифметика по модулю 2^N), а переполнение int -
//     неопределённое поведение. Результат остаётся верным для любых int.
void swapArithmetic(int& a, int& b) {
    if (&a == &b) {
        return;  // это одна и та же переменная
    }
    unsigned int ua = static_cast<unsigned int>(a);
    unsigned int ub = static_cast<unsigned int>(b);

    ua = ua + ub;  // ua = A + B
    ub = ua - ub;  // ub = A
    ua = ua - ub;  // ua = B

    a = static_cast<int>(ua);
    b = static_cast<int>(ub);
}

// Разворачивает массив на месте, обменивая элементы симметричных позиций.
// Параметры: arr - массив (передаётся как указатель, поэтому изменения видны
// вызывающей функции); size - количество элементов. Возвращает: ничего.
void reverseArray(int arr[], int size) {
    if (size <= 1) {
        return;  // граничный случай: пустой массив или один элемент
    }
    // Идём только до середины, иначе элементы поменяются дважды.
    // Здесь arr[i] и arr[size-1-i] - разные ячейки, защита &a == &b не срабатывает.
    for (int i = 0; i < size / 2; i++) {
        swapArithmetic(arr[i], arr[size - 1 - i]);
    }
}

// Выводит массив с подписью.
// Параметры: arr - массив (const - функция его не меняет);
//            size - число элементов;
//            label - подпись; const string& исключает копирование строки.
// Возвращает: ничего.
void printArray(const int arr[], int size, const string& label) {
    cout << label << ":";
    for (int i = 0; i < size; i++) {
        cout << " " << arr[i];
    }
    cout << endl;
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
