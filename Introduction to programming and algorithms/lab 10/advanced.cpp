// Работа с файлом: функция читает числа из файла и возвращает
// динамический массив и его размер ЧЕРЕЗ ССЫЛКИ.
// bool readNumbersFromFile(const string& filename, int*& data, int& size, int& errorCode)
// Что демонстрируется (требования повышенного уровня):
//   1. int*& data, int& size, int& errorCode - возврат нескольких значений
//      и кода ошибки через ссылки; динамическое выделение памяти.
//   2. Три способа передачи параметра: по значению, по указателю, по ссылке.
//   3. Функция, возвращающая ссылку на элемент массива, и её использование
//      в левой части присваивания; пример "висячей" ссылки в комментарии.
//   4. const string& - защита от копирования строки.
#include <iostream>
#include <fstream>
#include <limits>
#include <new>
#include <string>

const int INITIAL_CAPACITY = 4;  // начальная ёмкость массива (потом удваивается)
const string SAMPLE_FILE = "numbers.txt";

// Коды ошибок
const int ERR_OK = 0;
const int ERR_CANNOT_OPEN = 1;
const int ERR_EMPTY = 2;
const int ERR_BAD_DATA = 3;
const int ERR_MEMORY = 4;
const int ERR_BAD_INDEX = 5;

// ---------- Прототипы функций ----------
bool readNumbersFromFile(const string& filename, int*& data, int& size,
                         int& errorCode);
void freeNumbers(int*& data, int& size);
string describeError(int errorCode);
bool createSampleFile(const string& filename);
void printNumbers(const int* data, int size, const string& label);
void incrementByValue(int x);
void incrementByPointer(int* x);
void incrementByReference(int& x);
int& elementAt(int* data, int size, int index, int& errorCode);
void demonstratePassing(int* data, int size);
void demonstrateReturnedReference(int* data, int size);
void processFile(const string& filename);
string readLine(const string& pr);

int main() {
    bool running = true;
    while (running) {
        cout << "\n=== Меню ===" << endl;
        cout << "1 - создать тестовый файл " << SAMPLE_FILE << endl;
        cout << "2 - прочитать и обработать файл" << endl;
        cout << "0 - выход" << endl;

        string choice = readLine("Выбор: ");
        if (choice == "1") {
            if (createSampleFile(SAMPLE_FILE)) {
                cout << "Файл " << SAMPLE_FILE << " создан." << endl;
            } else {
                cout << "Ошибка: не удалось создать файл." << endl;
            }
        } else if (choice == "2") {
            string name = readLine("Имя файла (Enter = " + SAMPLE_FILE + "): ");
            if (name.empty()) {
                name = SAMPLE_FILE;
            }
            processFile(name);
        } else if (choice == "0") {
            running = false;
        } else {
            cout << "Ошибка: неизвестный пункт меню." << endl;
        }
    }
    return 0;
}

//Определения функций

// Читает целые числа из текстового файла в динамический массив.
// Параметры: filename - имя файла (const& - без копирования строки);
//            data - (ссылка на указатель) сюда записывается адрес нового массива;
//            size - (ссылка) сюда записывается число прочитанных чисел;
//            errorCode - (ссылка) сюда записывается код ошибки (ERR_*).
// Возвращает: true при успехе. При ошибке data = nullptr, size = 0.
// Память под массив выделяется через new[]; освобождать нужно freeNumbers().
// Ёмкость массива удваивается при нехватке места (размер файла заранее неизвестен).
bool readNumbersFromFile(const string& filename, int*& data, int& size,
                         int& errorCode) {
    data = nullptr;
    size = 0;
    errorCode = ERR_OK;

    ifstream file(filename);
    if (!file.is_open()) {
        errorCode = ERR_CANNOT_OPEN;
        return false;
    }

    int capacity = INITIAL_CAPACITY;
    int* buffer = new (nothrow) int[capacity];
    if (buffer == nullptr) {
        errorCode = ERR_MEMORY;
        return false;
    }

    int count = 0;
    int value;
    while (file >> value) {
        if (count == capacity) {  // место закончилось: выделяем массив вдвое больше
            int newCapacity = capacity * 2;
            int* bigger = new (nothrow) int[newCapacity];
            if (bigger == nullptr) {
                delete[] buffer;
                errorCode = ERR_MEMORY;
                return false;
            }
            for (int i = 0; i < count; i++) {
                bigger[i] = buffer[i];
            }
            delete[] buffer;  // старый массив больше не нужен
            buffer = bigger;
            capacity = newCapacity;
        }
        buffer[count] = value;
        count++;
    }
    // Цикл мог остановиться по концу файла (норма) или из-за нечислового текста
    if (!file.eof()) {
        delete[] buffer;
        errorCode = ERR_BAD_DATA;
        return false;
    }
    if (count == 0) {
        delete[] buffer;
        errorCode = ERR_EMPTY;
        return false;
    }

    data = buffer;
    size = count;
    return true;
}

// Освобождает динамический массив и обнуляет указатель и размер.
// Параметры: data - ссылка на указатель (после вызова nullptr);
//            size - ссылка на размер (после вызова 0).
// Возвращает: ничего.
// Ссылка на указатель нужна, чтобы обнулить именно указатель вызывающей функции:
// это защищает от повторного delete и обращения к освобождённой памяти.
void freeNumbers(int*& data, int& size) {
    delete[] data;
    data = nullptr;
    size = 0;
}
// Преобразует код ошибки в текст.
// Параметры: errorCode - код (ERR_*).
// Возвращает: описание ошибки.
string describeError(int errorCode) {
    switch (errorCode) {
        case ERR_OK:          return "ошибок нет";
        case ERR_CANNOT_OPEN: return "не удалось открыть файл (проверьте имя)";
        case ERR_EMPTY:       return "файл не содержит чисел";
        case ERR_BAD_DATA:    return "в файле встретился нечисловой текст";
        case ERR_MEMORY:      return "не хватило памяти";
        case ERR_BAD_INDEX:   return "индекс вне границ массива";
        default:              return "неизвестная ошибка";
    }
}

// Создаёт тестовый файл с 10 числами (больше INITIAL_CAPACITY, чтобы сработало
// увеличение массива).
// Параметры: filename - имя создаваемого файла.
// Возвращает: true, если файл записан.
bool createSampleFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << "10 20 30 40 50\n60 70 80 90 100\n";
    return true;
}

// Выводит массив с подписью.
// Параметры: data - массив (const - не изменяется); size - число элементов;
//            label - подпись (const string& - без копирования).
// Возвращает: ничего.
void printNumbers(const int* data, int size, const string& label) {
    cout << label << " (" << size << " шт.):";
    for (int i = 0; i < size; i++) {
        cout << " " << data[i];
    }
    cout << endl;
}

// ---------- Три способа передачи параметра ----------

// ПО ЗНАЧЕНИЮ: функция получает копию, исходная переменная не меняется.
// Когда использовать: маленькие типы (int, double, char), когда менять оригинал не нужно.
void incrementByValue(int x) {
    x = x + 1;  // изменяется только локальная копия
}

// ПО УКАЗАТЕЛЮ: передаётся адрес, оригинал меняется через разыменование.
// Когда использовать: адрес может отсутствовать (nullptr), работа с массивами
// и динамической памятью, совместимость с C.
void incrementByPointer(int* x) {
    if (x != nullptr) {  // указатель обязательно проверяем
        *x = *x + 1;
    }
}

// ПО ССЫЛКЕ: ссылка - другое имя той же переменной, оригинал меняется.
// Когда использовать: нужно изменить аргумент или вернуть несколько значений,
// и nullptr быть не может (ссылка всегда указывает на существующий объект).
// Для больших объектов, которые не меняются, используют const T&.
void incrementByReference(int& x) {
    x = x + 1;
}

// Показывает разницу между тремя способами на первом элементе массива.
// Параметры: data - массив; size - число элементов (должно быть > 0).
// Возвращает: ничего.
void demonstratePassing(int* data, int size) {
    if (data == nullptr || size <= 0) {
        return;
    }
    cout << "\n--- Три способа передачи ---" << endl;
    cout << "data[0] исходно: " << data[0] << endl;

    incrementByValue(data[0]);
    cout << "После incrementByValue(data[0]):     " << data[0]
              << "  (не изменился: передана копия)" << endl;

    incrementByPointer(&data[0]);
    cout << "После incrementByPointer(&data[0]):  " << data[0]
              << "  (изменился через указатель)" << endl;

    incrementByReference(data[0]);
    cout << "После incrementByReference(data[0]): " << data[0]
              << "  (изменился через ссылку)" << endl;
}

//Возврат ссылки
// Возвращает ССЫЛКУ на элемент массива, поэтому результат можно использовать
// слева от знака присваивания: elementAt(data, size, 2, err) = 999;
// Параметры: data - массив; size - число элементов; index - номер элемента;
//            errorCode - (ссылка) код ошибки.
// Возвращает: ссылку на data[index]. При неверном индексе пишет ERR_BAD_INDEX
// и возвращает ссылку на статическую "заглушку" (запись в неё ничего не портит).
// ОСТОРОЖНО: ссылку нельзя возвращать на локальную переменную - после выхода из
// функции она "повиснет" (висячая ссылка, неопределённое поведение):
//     int& bad() { int local = 5; return local; }   // ОШИБКА!
// Здесь возвращается ссылка на элемент массива, который живёт дольше функции,
// либо на static-переменную, которая существует всё время работы программы.
int& elementAt(int* data, int size, int index, int& errorCode) {
    static int dummy = 0;
    if (data == nullptr || index < 0 || index >= size) {
        errorCode = ERR_BAD_INDEX;
        dummy = 0;
        return dummy;
    }
    errorCode = ERR_OK;
    return data[index];
}

// Демонстрирует использование elementAt слева от присваивания.
// Параметры: data - массив; size - число элементов.
// Возвращает: ничего.
void demonstrateReturnedReference(int* data, int size) {
    cout << "\n--- Возврат ссылки на элемент ---" << endl;
    int errorCode = ERR_OK;

    elementAt(data, size, size - 1, errorCode) = 999;  // меняем последний элемент
    cout << "elementAt(последний) = 999, код: " << errorCode << " ("
              << describeError(errorCode) << ")" << endl;

    elementAt(data, size, size, errorCode) = 555;  // индекс вне границ
    cout << "elementAt(индекс " << size << ") = 555, код: " << errorCode << " ("
              << describeError(errorCode) << ")" << endl;

    printNumbers(data, size, "Массив после изменений");
}

// Полный сценарий: чтение файла, вывод, демонстрации, освобождение памяти.
// Параметры: filename - имя файла.
// Возвращает: ничего.
void processFile(const string& filename) {
    int* data = nullptr;
    int size = 0;
    int errorCode = ERR_OK;

    if (!readNumbersFromFile(filename, data, size, errorCode)) {
        cout << "Ошибка чтения (код " << errorCode << "): "
                  << describeError(errorCode) << endl;
        return;
    }

    printNumbers(data, size, "Прочитано из файла");
    demonstratePassing(data, size);
    demonstrateReturnedReference(data, size);

    freeNumbers(data, size);  // освобождаем память; data станет nullptr
    cout << "\nПамять освобождена (data == nullptr: "
              << (data == nullptr ? "да" : "нет") << ")." << endl;
}

// Читает строку целиком (с пробелами).
// Параметры: pr - приглашение к вводу.
// Возвращает: введённую строку (пустую при конце ввода).
string readLine(const string& pr) {
    cout << pr;
    string line;
    if (!getline(cin, line)) {
        return "0";  // конец ввода трактуем как выход, чтобы не зациклиться
    }
    return line;
}
