#include <iostream>

using namespace std;

int main() {
    	setlocale(LC_ALL, "RUSSIAN");
	// Ввод переменных
	int min, h;
	cout << "Перевод из часов в минуты." << endl;;
	cout << "Введите количество минут: ";
	// Ввод часов
	cin >> h;
	// Проверяем, правильно ли пользователь ввёл число.
	// Если введён текст вместо числа, cin перейдёт в состояние ошибки.
	if (cin.fail() || h < 0) {
		cout << "Ошибка ввода.";
		return 1;
	}
	// Перевод из часов в минуты
	min = h * 60;
	cout << h << " ч. = " << min << " мин." << endl;


return 0;
}
