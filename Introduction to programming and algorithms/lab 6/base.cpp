#include <iostream>
#include <iomanip>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()

int main() {
    const int SIZE = 10;        // размер массива 
    const int MIN_VALUE = 10;   // нижняя граница диапазона
    const int MAX_VALUE = 99;   // верхняя граница диапазона
    const int LIMIT = 50;       // значение, с которым сравниваем
    int arr[SIZE];              // статический массив

    // Генератор инициализируем один раз текущим временем
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Заполнение: формула min + rand() % (max - min + 1) даёт 10..99
    for (int i = 0; i < SIZE; i++) {
        arr[i] = MIN_VALUE + std::rand() % (MAX_VALUE - MIN_VALUE + 1);
    }

    // Форматированный вывод массива
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cout << std::setw(4) << arr[i];
    }
    std::cout << std::endl;

    // Подсчёт: количество элементов больше LIMIT.
    // Цикл for, т.к. число итераций известно заранее.
    int countGreater = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] > LIMIT) {
            countGreater++;
        }
    }

    std::cout << "Количество элементов больше " << LIMIT << ": "
              << countGreater << std::endl;
    return 0;
}
