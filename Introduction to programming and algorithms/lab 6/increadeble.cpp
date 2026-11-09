// ============================================================
// ЛР №6. Повышенный уровень, вариант 11
// Задание: массив из 20 случайных чисел 1..100;
//          вычислить медиану (средний элемент отсортированного
//          массива). Исходный массив не изменяется.
// ============================================================
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

const int SIZE = 20;
const int MIN_VALUE = 1;
const int MAX_VALUE = 100;
const int PER_LINE = 10;

// Вывод массива столбцами; size передаём отдельно, т.к. sizeof
// внутри функции вернул бы размер указателя.
void printArray(const int arr[], int size, const char* title) {
    std::cout << title << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(5) << arr[i];
        if ((i + 1) % PER_LINE == 0) {
            std::cout << std::endl;
        }
    }
}

// Сортировка пузырьком по возрастанию.
// Внешний цикл: после каждого прохода максимальный элемент
// "всплывает" в конец, поэтому внутренний цикл сокращается.
void bubbleSort(int arr[], int size) {
    for (int pass = 0; pass < size - 1; pass++) {
        bool swapped = false;                  // был ли обмен на проходе
        for (int j = 0; j < size - 1 - pass; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];             // temp нужен, чтобы
                arr[j] = arr[j + 1];           // не потерять arr[j]
                arr[j + 1] = temp;             // при перезаписи
                swapped = true;
            }
        }
        if (!swapped) break;                   // уже отсортирован
    }
}

// Медиана отсортированного массива.
// Чётный размер: среднее двух центральных элементов,
// нечётный: центральный элемент.
double median(const int sorted[], int size) {
    if (size <= 0) {                           // защита от пустого массива
        return 0.0;
    }
    if (size % 2 == 0) {
        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }
    return sorted[size / 2];
}

int main() {
    int arr[SIZE];

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = MIN_VALUE + std::rand() % (MAX_VALUE - MIN_VALUE + 1);
    }
    printArray(arr, SIZE, "Исходный массив:");

    // Сортируем копию, чтобы не испортить исходный массив
    int sortedArr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sortedArr[i] = arr[i];
    }
    bubbleSort(sortedArr, SIZE);
    printArray(sortedArr, SIZE, "\nОтсортированная копия:");

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "\nМедиана: " << median(sortedArr, SIZE) << std::endl;
    return 0;
}
