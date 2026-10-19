#include <iostream>

using namespace std;

int main() {
setlocale(LC_ALL, "RU");
 cout << "Определение количества дней в месяце." << endl;
 int month = 0;
 cout << "Введите номер месяца(1-12): " << endl;
 cin >> month;
  if(cin.fail()) {
    cout << "Ошибка. Введите правильное значение." << endl;
    return 1;
  }
 switch(month) {
    // Январь(1), Март(3), Май(5), Июль(7), Август(8), Октябрь(10), Декабрь(12)
case 1:
case 3:
case 5:
case 7:
case 8:
case 10:
case 12:
cout << "В этом месяце 31 день. " << endl;
 break;
 // Апрель(4), Июнь(6), Сентябрь(9), Ноябрь(11)
 case 4:
 case 6:
 case 11:
 cout << "В этом месяце 30 дней. " << endl;
  break;
  // Февраль(2)
  case 2:
  cout << "В этом месяце 28 дней. " << endl;
  break;
  default:
  cout << "Ошибка. Введите число от 1 до 12." << endl;
  break;
 }



    return 0;
}