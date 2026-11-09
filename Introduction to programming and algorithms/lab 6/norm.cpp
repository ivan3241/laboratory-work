// ============================================================
// ЛР №6. Средний уровень, вариант 11
// Задание: массив из 15 случайных чисел 0..100;
//          найти, сколько раз встречается максимальный элемент.
// Дополнительно: сумма, среднее, минимум (комплексная обработка).
// ============================================================
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

int main() {
    const int SIZE = 15;
    const int MIN_VALUE = 0;
    const int MAX_VALUE = 100;
    const int PER_LINE = 5;     // элементов в строке при выводе
    int arr[SIZE];

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = MIN_VALUE + std::rand() % (MAX_VALUE - MIN_VALUE + 1);
    }

    // Вывод в виде столбцов с выравниванием
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cout << std::setw(5) << arr[i];
        if ((i + 1) % PER_LINE == 0) {
            std::cout << std::endl;
        }
    }

    // Один проход: сумма, минимум и максимум.
    // Начинаем с arr[0], цикл идёт с i = 1 (нулевой элемент уже учтён).
    int sum = arr[0];
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < SIZE; i++) {
        sum += arr[i];
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // Среднее: приведение к double, иначе деление целочисленное
    double average = static_cast<double>(sum) / SIZE;

    // Основное задание: максимум нужно знать заранее,
    // поэтому считаем его вхождения вторым проходом.
    int maxCount = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == maxVal) {
            maxCount++;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n=== РЕЗУЛЬТАТЫ ===" << std::endl;
    std::cout << "Сумма элементов:        " << sum << std::endl;
    std::cout << "Среднее арифметическое: " << average << std::endl;
    std::cout << "Минимальный элемент:    " << minVal << std::endl;
    std::cout << "Максимальный элемент:   " << maxVal << std::endl;
    std::cout << "Максимум встречается раз: " << maxCount << std::endl;
    return 0;
}
