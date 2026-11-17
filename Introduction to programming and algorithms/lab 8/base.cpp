// Задание: ввести строку и заменить все символы 'a' на 'b'.
#include <iostream>
#include <string>

using namespace std;

const char OLD_CHAR = 'a';  // какой символ заменяем
const char NEW_CHAR = 'b';  // на какой символ заменяем

int main() {
    string text;

    // getline читает строку целиком, вместе с пробелами
    cout << "Введите строку: ";
    getline(cin, text);

    // Проверка на пустую строку
    if (text.empty()) {
        cout << "Строка пустая, заменять нечего." << endl;
        return 0;
    }

    string result = text;  // работаем с копией, исходная строка сохраняется
    int replacedCount = 0;      // сколько замен выполнено

    // Range-based for со ссылкой (char&), чтобы изменять символы прямо в строке
    for (char& symbol : result) {
        if (symbol == OLD_CHAR) {
            symbol = NEW_CHAR;
            replacedCount++;
        }
    }

    cout << "\nИсходная строка: \"" << text << "\"" << endl;
    cout << "Результат:       \"" << result << "\"" << endl;
    cout << "Выполнено замен '" << OLD_CHAR << "' -> '" << NEW_CHAR << "': "
              << replacedCount << endl;

    return 0;
}
