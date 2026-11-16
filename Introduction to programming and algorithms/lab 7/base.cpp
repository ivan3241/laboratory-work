// Матрица 4x4, заполнение с клавиатуры.
// Задание: вывести элементы выше главной диагонали.
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

const int SIZE = 4;         //размер квадратной матрицы
const int CELL_WIDTH = 6;   //ширина ячейки при выводе

// Безопасный ввод целого числа: повторяет запрос, пока не введено число
int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Ошибка: нужно ввести целое число!" << std::endl;
        std::cin.clear();  //снимаем флаг ошибки потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    int matrix[SIZE][SIZE];

    //Заполнение с клавиатуры
    std::cout << "Введите элементы матрицы " << SIZE << "x" << SIZE << ":" << std::endl;
    for (int i = 0; i < SIZE; i++) {          // строки
        for (int j = 0; j < SIZE; j++) {      // столбцы
            matrix[i][j] = readInt("matrix[" + std::to_string(i) + "][" +
                                   std::to_string(j) + "] = ");
        }
    }

    //Вывод матрицы
    std::cout << "\nМатрица:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << std::setw(CELL_WIDTH) << matrix[i][j];
        }
        std::cout << std::endl;
    }

    //Элементы выше главной диагонали
    //Это элементы, у которых номер столбца больше номера строки (j > i),
    //поэтому внутренний цикл начинается с j = i + 1.
    std::cout << "\nЭлементы выше главной диагонали:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            std::cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j]
                      << std::endl;
        }
    }

    return 0;
}
