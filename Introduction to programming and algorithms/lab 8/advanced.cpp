//Задание: сгенерировать и вывести все подстроки заданной строки.
//Подстрока однозначно задаётся началом (start) и длиной (len).
//Перебор: длина от 1 до n, начало от 0 до n - len. Тогда
//start + len <= n, и substr никогда не выходит за границы.
//Всего подстрок (с учётом повторов): n * (n + 1) / 2.
#include <iostream>
#include <string>
#include <set>

using namespace std;

const size_t MAX_LENGTH = 30;  //ограничение, чтобы вывод не был огромным

// Чтение строки с проверкой: не пустая и не длиннее MAX_LENGTH
string readValidString() {
    string text;
    while (true) {
        cout << "Введите строку (1.." << MAX_LENGTH << " символов): ";
        getline(cin, text);

        if (text.empty()) {
            cout << "Ошибка: строка пустая!" << endl;
        } else if (text.length() > MAX_LENGTH) {
            cout << "Ошибка: строка слишком длинная (" << text.length()
                      << " символов)!" << endl;
        } else {
            return text;
        }
        if (!cin) {  // конец ввода (EOF) — чтобы не зациклиться
            cout << "Ввод прерван." << endl;
            return "";
        }
    }
}

int main() {
    string text = readValidString();
    if (text.empty()) {
        return 0;
    }

    const size_t n = text.length();
    size_t count = 0;                 // количество найденных подстрок
    set<string> uniqueSubs; // множество без повторов (для статистики)

    cout << "\nВсе подстроки строки \"" << text << "\":" << endl;

    // Внешний цикл — длина подстроки
    for (size_t len = 1; len <= n; len++) {
        cout << "Длина " << len << ":";
        // Внутренний цикл — позиция начала подстроки
        for (size_t start = 0; start + len <= n; start++) {
            string sub = text.substr(start, len);  // границы гарантированно верны
            cout << " \"" << sub << "\"";
            uniqueSubs.insert(sub);
            count++;
        }
        cout << endl;
    }

    cout << "\nВсего подстрок (с повторами): " << count << endl;
    cout << "Проверка по формуле n*(n+1)/2: " << n * (n + 1) / 2 << endl;
    cout << "Уникальных подстрок: " << uniqueSubs.size() << endl;

    return 0;
}
