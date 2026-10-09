#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");
    int a, b, c;
    cout << "Введите 3 значаения: " << endl;
    cin >> a >> b >> c;
        
    if (std::cin.fail()) {
        cout << "Ошибка ввода!\n";
        return 1;
    }
    int f=a+b+c;
    if(f > 100) {
        cout << "Большая сумма.";
    }
    else {
        cout << "Сумма: " << f << endl;
    }






    return 0;
}
