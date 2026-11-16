// Матрица 3x3, значения 1..100.
// Задание: определить, является ли матрица магическим квадратом
// (суммы всех строк, всех столбцов и обеих диагоналей равны).
// Режимы заполнения: 1 - случайно, 2 - с клавиатуры,
// 3 - готовый магический квадрат (для проверки программы).
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

const int SIZE = 3;
const int MIN_VALUE = 1;
const int MAX_VALUE = 100;
const int CELL_WIDTH = 5;

//Ввод целого числа в диапазоне [low, high] с защитой от некорректного ввода
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

int main() {
    int matrix[SIZE][SIZE];

    int mode = readIntInRange("Заполнение: 1 - случайное, 2 - с клавиатуры, "
                              "3 - магический квадрат: ", 1, 3);

    if (mode == 1) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = MIN_VALUE + std::rand() % (MAX_VALUE - MIN_VALUE + 1);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = readIntInRange(
                    "matrix[" + std::to_string(i) + "][" + std::to_string(j) + "] = ",
                    MIN_VALUE, MAX_VALUE);
            }
        }
    } else {
        const int magic[SIZE][SIZE] = {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = magic[i][j];
            }
        }
    }

    //Вывод матрицы
    std::cout << "\nМатрица " << SIZE << "x" << SIZE << ":" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << std::setw(CELL_WIDTH) << matrix[i][j];
        }
        std::cout << std::endl;
    }

    //Сумма главной и побочной диагоналей
    int sumMain = 0;       // [i][i]
    int sumSecondary = 0;  // [i][SIZE-1-i]
    for (int i = 0; i < SIZE; i++) {
        sumMain += matrix[i][i];
        sumSecondary += matrix[i][SIZE - 1 - i];
    }
    std::cout << "\nСумма главной диагонали: " << sumMain << std::endl;
    std::cout << "Сумма побочной диагонали: " << sumSecondary << std::endl;

    // Эталонная сумма — сумма главной диагонали; с ней сравниваем всё остальное
    const int target = sumMain;
    bool isMagic = (sumSecondary == target);

    //Суммы по строкам
    std::cout << "\nСуммы по строкам:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        int rowSum = 0;
        for (int j = 0; j < SIZE; j++) {
            rowSum += matrix[i][j];
        }
        std::cout << "  Строка " << i << ": " << rowSum << std::endl;
        if (rowSum != target) {
            isMagic = false;
        }
    }

    //Суммы по столбцам
    std::cout << "\nСуммы по столбцам:" << std::endl;
    for (int j = 0; j < SIZE; j++) {
        int colSum = 0;
        for (int i = 0; i < SIZE; i++) {
            colSum += matrix[i][j];
        }
        std::cout << "  Столбец " << j << ": " << colSum << std::endl;
        if (colSum != target) {
            isMagic = false;
        }
    }

    //Результат
    if (isMagic) {
        std::cout << "\nМатрица ЯВЛЯЕТСЯ магическим квадратом (сумма = " << target
                  << ")." << std::endl;
    } else {
        std::cout << "\nМатрица НЕ является магическим квадратом." << std::endl;
    }

    return 0;
}