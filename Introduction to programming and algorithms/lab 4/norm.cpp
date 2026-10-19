#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
double num1 = 0.0;
double num2 = 0.0;
char oper = ' ';
cout << "Калькулятор (+, -, %, ^, *)";
cout << "Введите 1 число: " << endl;
if(!(cin >> num1)) {
    cout << "Ошибка. Некорректный ввод. " << endl;
    return 1;
}
cout << "Введите операцию (+,-,*,%,^): " << endl;
cin >> oper;
cout << "Введите 2 число: " << endl;
if(!(cin >> num2)) {
    cout << "Ошибка. Некорректный ввод. " << endl;
    return 1;
}
switch (oper) {
    case '+': // Сложение
    cout << num1 << " + " << num2 << " = " << (num1+num2) << endl;
    break;
      
    case '-': // Разность
    cout << num1 << " - " << num2 << " = " << (num1-num2) << endl;
    break;  
    
    case '*': // Умножение
    cout << num1 << " * " << num2 << " = " << (num1*num2) << endl;
    break;
    case '/': // Деление
    if(num2 == 0){
        cout << "Ошибка. На 0 делить нельзя." << endl;
    } else {
    cout << num1 << " / " << num2 << " = " << (num1/num2) << endl;
    }
    break;
    
    case '^': // Возведение в степень
    cout << "Результат: " << num1 << " ^ " << num2 << " = " << pow(num1, num2) << endl;
    break;

    case '%': // Остаток от деления (только для целых чисел) 
    {
    long long int1 = static_cast<long long>(num1);
    long long int2 = static_cast<long long>(num2);

    if (int2 == 0) {
    cout << "Ошибка: деление на ноль при вычислении остатка!" << endl;
    } else {
    cout << "Результат (" << int1 << " % " << int2 << "): " << (int1 % int2) << std::endl;
    if (num1 != int1 || num2 != int2) {
    cout << "(Примечание: дробная часть была отброшена)" << endl;
    }
    }
    }
    break;

    default: // Обработка неизвестного знака операции
    cout << "Ошибка: неизвестная операция '" << oper << "'!" << std::endl;
            break;
}



    return 0;
}