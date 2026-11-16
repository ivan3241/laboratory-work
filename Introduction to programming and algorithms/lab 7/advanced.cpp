// Матрица 5x5, значения 1..100.
// Задание: добавить строку в конец матрицы (значения вводятся).
//
// Статический массив нельзя "растянуть" во время работы, поэтому
// память выделяется с запасом (MAX_ROWS строк), а реальное число
// строк хранится в переменной rows.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

const int START_ROWS = 5;   // начальное количество строк
const int COLS = 5;         // количество столбцов
const int MAX_ROWS = 10;    // максимум строк (запас под добавление)
const int MIN_VALUE = 1;
const int MAX_VALUE = 100;
const int CELL_WIDTH = 5;

// Ввод целого числа в диапазоне [low, high] с защитой от букв и выхода за границы
int readIntInRange(const std::string& prompt, int low, int high) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= low && value <= high) {
                return value;
            }
            std::cout << "Ошибка: число должно быть от " << low << " до " << high
                      << "!" << std::endl;
        } else {
            std::cout << "Ошибка: нужно ввести целое число!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Вывод первых rows строк матрицы
void printMatrix(const int matrix[][COLS], int rows, const std::string& title) {
    std::cout << title << " (" << rows << "x" << COLS << "):" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << std::setw(CELL_WIDTH) << matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Добавление строки в конец. Возвращает true, если строка добавлена.
bool appendRow(int matrix[][COLS], int& rows) {
    // Контроль границ: свободное место есть, только пока rows < MAX_ROWS
    if (rows >= MAX_ROWS) {
        std::cout << "Ошибка: матрица заполнена, добавить строку нельзя (максимум "
                  << MAX_ROWS << " строк)." << std::endl;
        return false;
    }
    std::cout << "Введите значения новой строки (" << MIN_VALUE << ".." << MAX_VALUE
              << "):" << std::endl;
    for (int j = 0; j < COLS; j++) {
        // Новая строка записывается в индекс rows — сразу за последней строкой
        matrix[rows][j] = readIntInRange(
            "новая_строка[" + std::to_string(j) + "] = ", MIN_VALUE, MAX_VALUE);
    }
    rows++;  // теперь в матрице на одну строку больше
    return true;
}

int main() {
    int matrix[MAX_ROWS][COLS];
    int rows = START_ROWS;  // текущее число строк

    //Заполнение случайными числами
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = MIN_VALUE + std::rand() % (MAX_VALUE - MIN_VALUE + 1);
        }
    }

    printMatrix(matrix, rows, "Исходная матрица");

    //Добавление строк (можно повторять до предела MAX_ROWS)
    bool again = true;
    while (again) {
        if (appendRow(matrix, rows)) {
            std::cout << std::endl;
            printMatrix(matrix, rows, "Матрица после добавления строки");
        }
        if (rows >= MAX_ROWS) {
            break;  // больше добавлять некуда
        }
        again = (readIntInRange("Добавить ещё одну строку? (1 - да, 0 - нет): ", 0, 1)
                 == 1);
    }

    return 0;
}
