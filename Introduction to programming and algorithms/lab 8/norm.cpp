// Задание: найти позицию первого вхождения символа 'x'
// (вывести -1, если символа нет).
// Дополнительно (комплексная обработка с <cctype>): подсчёт букв,
// цифр, пробелов, прочих символов; преобразование регистра.
#include <iostream>
#include <string>
#include <cctype>  // isalpha, isdigit, isspace, toupper, tolower

const char SEARCH_CHAR = 'x';

using namespace std;

int main() {
    string text;

    cout << "Введите строку: ";
    getline(cin, text);

    // Корректная обработка пустой строки
    if (text.empty()) {
        cout << "Строка пустая: обрабатывать нечего." << endl;
        return 0;
    }

    //1. Позиция первого вхождения 'x'
    // find возвращает string::npos, если символ не найден.
    // Сравнивать нужно именно с npos (а не с 0 или -1 напрямую).
    size_t position = text.find(SEARCH_CHAR);
    int answer = -1;  // по условию, если символа нет — выводим -1
    if (position != string::npos) {
        answer = static_cast<int>(position);
    }
    cout << "\nПозиция первого символа '" << SEARCH_CHAR << "': " << answer
              << endl;

    //2. Подсчёт символов по типам (<cctype>)
    int letterCount = 0;
    int digitCount = 0;
    int spaceCount = 0;
    int otherCount = 0;

    for (char symbol : text) {
        // приведение к unsigned char — безопасный вызов функций <cctype>
        unsigned char code = static_cast<unsigned char>(symbol);
        if (isalpha(code)) {
            letterCount++;
        } else if (isdigit(code)) {
            digitCount++;
        } else if (isspace(code)) {
            spaceCount++;
        } else {
            otherCount++;
        }
    }

    cout << "\n=== Статистика ===" << endl;
    cout << "Длина строки: " << text.length() << endl;
    cout << "Букв (латиница): " << letterCount << endl;
    cout << "Цифр: " << digitCount << endl;
    cout << "Пробелов: " << spaceCount << endl;
    cout << "Других символов: " << otherCount << endl;

    //3. Преобразование регистра
    string upperText = text;
    string lowerText = text;
    for (char& symbol : upperText) {
        symbol = static_cast<char>(toupper(static_cast<unsigned char>(symbol)));
    }
    for (char& symbol : lowerText) {
        symbol = static_cast<char>(tolower(static_cast<unsigned char>(symbol)));
    }

    cout << "\nВерхний регистр: " << upperText << endl;
    cout << "Нижний регистр:  " << lowerText << endl;

    return 0;
}
