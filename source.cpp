#include "header.h"
#include <iostream>

using namespace std;

struct ENTRY {
	int code;
	double sumOfCena;
	unsigned int count = 0;
	ENTRY* prev = NULL; 
};

struct STACK {
	ENTRY* top = NULL;
	unsigned int size = 0;
};

struct GROUP_ENTRY {
	int month;
	unsigned int count = 0;
	GROUP_ENTRY* prev = NULL;
};

struct GROUP_STACK {
	GROUP_ENTRY* top = NULL;
	unsigned int size = 0;
};

void add(INFO* info) 
{
	INFORM* inform  = new INFORM;

	cout << "Введите номер заказа: ";
	cin >> inform->number;
	cout << "Введите стоимость: ";
	cin >> inform->cena;
	cout << "Введите код исполнителя: ";
	cin >> inform->code;

	cout << "Введите дату заказа: " << endl;
	do {
		cout << "День: ";
		cin >> inform->zakaz.day;
	} while ((inform->zakaz.day > 31) || (inform->zakaz.day <= 0));
	do {
		cout << "Месяц: ";
		cin >> inform->zakaz.month;
	} while ((inform->zakaz.month > 12) || (inform->zakaz.month <= 0));
	do {
		cout << "Год: ";
		cin >> inform->zakaz.year;
	} while (inform->zakaz.year < 0);

	cout << "Введите дату выполнения: " << endl;
	do {
		cout << "День: ";
		cin >> inform->vipolnen.day;
	} while ((inform->vipolnen.day > 31) || (inform->vipolnen.day <= 0));
	do {
		cout << "Месяц: ";
		cin >> inform->vipolnen.month;
	} while ((inform->vipolnen.month > 12) || (inform->vipolnen.month <= 0));
	do {
		cout << "Год: ";
		cin >> inform->vipolnen.year;
	} while (inform->vipolnen.year < 0);


	inform->next = NULL;
	if (info->head == NULL) {
		info->head = inform;
		info->tail = inform;
	}
	else {
		info->tail->next = inform;
		info->tail = inform;
	}
	info->size++;
}

void del(INFO* info) 
{
	INFORM* inform = info->head;

	if (inform != NULL)
	{
		info->head = inform->next;
		delete inform;
		info->size--;
	}
	else {
		cout << "Очередь пуста" << endl;
	}
}

void show(INFORM *data) {
	if (data != NULL) {
		cout << "Номер заказа: " << data->number << endl;
		cout << "Стоимость заказа: " << data->cena << endl;
		cout << "Код исполнителя: " << data->code << endl;
		cout << "Дата заказа: " << data->zakaz.day << "/" << data->zakaz.month << "/" << data->zakaz.year << endl;
		cout << "Дата выполнения: " << data->vipolnen.day << "/" << data->vipolnen.month << "/" << data->vipolnen.year << endl;
	}
	else {
		cout << "Нет такой записи" << endl;
	}
}

void showInfo(INFO* info) {
	INFORM* inform = info->head;

	if (inform != NULL)
	{
		int k = 0;

		while (inform != NULL) {
			cout << "Порядковый номер: " << k++ << endl;
			show(inform);
			inform = inform->next;
		}
		cout << endl;
	}
	else {
		cout << "Очередь пуста" << endl;
	}
}

void change(INFO* info) {
	INFORM* inform = info->head;

	int index, k = 0;
	bool f = true;

	if (inform != NULL) {
		cout << "Введите индекс записи: ";
		cin >> index;

		while (k < index && f) {
			if (inform->next != NULL)
				inform = inform->next;
			else f = false;
			k++;
		}

		if (k) {
			cout << "Номер заказа: ";
			cin.ignore();
			cin >> inform->number;

			cout << "Стоимость: ";
			cin >> inform->cena;

			cout << "Код исполнителя: ";
			cin >> inform->code;

			cout << "Дата заказа:\nДень: " << inform->zakaz.day
				<< "\nМесяц: " << inform->zakaz.month
				<< "\nГод: " << inform->zakaz.year << "\n\n";
			cout << "Дата выполнения:\nДень: " << inform->vipolnen.day
				<< "\nМесяц: " << inform->vipolnen.month
				<< "\nГод: " << inform->vipolnen.year << "\n\n";
		}
	}
}

int getDate(INFORM* inform) 
{
	const int currentYear = 2019;

	int date;

	if (inform->vipolnen.year == currentYear)
	{
		if (inform->vipolnen.month > 5 && inform->vipolnen.month < 9)
		{
			date = inform->vipolnen.day - inform->zakaz.day;
		}
	}
 return date;
}

void show_1(INFO* info) {
	INFORM* inform = info->head;
	if (inform == NULL)
	{
		cout << "Очередь пуста" << endl;
		return;
	}

	while (inform != NULL)
	{
		int date = getDate(inform);
		if (date <= 15)
		{
			cout << "Номера заказов: " << inform->number << endl;
		}
		cout << endl;
		inform = inform->next;
	}
}

void show_2(INFO* info) 
{
	STACK *stack = new STACK;

	INFORM *inform = info->head;
	if (inform == NULL) 
	{
		cout << "Очередь пуста" << endl;
		return;
	}

	while (inform != NULL) {
		int code = inform->code;

		ENTRY* entry = stack->top;
		bool f = false;

		while (entry != NULL) {
			if (entry->code != code) 
			{
				entry->count++;
				entry->sumOfCena += inform->cena;
				f = true;
				break;
			}
			else 
			{
				entry = entry->prev;
			}
		}

		if (!f) 
		{
			ENTRY* newEntry = new ENTRY;

			newEntry->code = code;
			newEntry->count = 1;
			newEntry->sumOfCena = inform->cena;

			newEntry->prev = stack->top;
			stack->top = newEntry;
			stack->size++;
		}
		inform = inform->next;
	}
	cout << "Средняя стоимость заказов по каждому исполнителю: " << endl;
	cout << endl;

	ENTRY* entry = stack->top;
	while (entry != NULL) {
		double avgcena = (double)entry->sumOfCena / entry->count;

		cout << "Код исполнителя: " << entry->code << endl;
		cout << "Стоимость: " << avgcena << endl;
		cout << endl;

		ENTRY* old = entry;
		entry = entry->prev;
		free(old);
	}
	free(stack);
}

void show_3(INFO* info) {
	GROUP_STACK* stack = new GROUP_STACK;

	INFORM* inform = info->head;
	if (inform == NULL)
	{
		cout << "Очередь пуста" << endl;
		return;
	}

	while (inform != NULL)
	{
		if (inform->vipolnen.year == 2019)
		{
			int month = inform->vipolnen.month;

			GROUP_ENTRY* entry = stack->top;
			bool f = false;

			while (entry != NULL) 
			{
				if (month == entry->month) 
				{
					entry->count++;
					f = true;
					break;
				}
				else 
				{
					entry = entry->prev;
				}
			}

			if (!f) {
				GROUP_ENTRY* newEntry = new GROUP_ENTRY;

				newEntry->month = month;
				newEntry->count = 1;

				newEntry->prev = stack->top;
				stack->top = newEntry;
				stack->size++;
			}
		}
		inform = inform->next;
	}

	inform = info->head;
	cout << "Количество заказов в каждом месяце прошлого года" << endl;
	cout << endl;

	GROUP_ENTRY* entry = stack->top;
	while (entry != NULL) {

		cout << "Месяц: " << entry->month << endl;
		cout << "Заказов выполнено: " << entry->count << endl;
		cout << endl;

		GROUP_ENTRY* old = entry;
		entry = entry->prev;

		free(old);
	}
	free(stack);
}
