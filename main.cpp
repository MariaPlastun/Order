#include <iostream>
#include "header.h"
#include <clocale>

using namespace std;

int main(int t, const char* tv[]) 
{
	setlocale(LC_ALL, "Russian");
	INFO* info = new INFO;

	cout << "1. Добавить запись" << endl;
	cout << "2. Удалить запись" << endl;
	cout << "3. Посмотреть очередь" << endl;
	cout << "4. Изменить запись" << endl;
	cout << "5. Заказы выполненные меньше чем за 15 дней летом прошлого года" << endl;
	cout << "6. Общая стоимость заказов" << endl;
	cout << "7. Количество выполненных заказов за каждый месяц прошлого года" << endl;
	cout << "8. Закончить редактирование" << endl;

	int n;
	do {
		cout << endl << "Выбирайте: ";
		cin >> n;
		switch (n) {
		case 1: add(info); break;
		case 2: del(info);  break;
		case 3: showInfo(info); break;
		case 4: change(info); break;
		case 5: show_1(info); break;
		case 6: show_2(info); break;
		case 7: show_3(info); break;
		case 0: break;
		}
	} while (n);
	return 0;
}
