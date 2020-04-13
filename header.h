#ifndef Header_h
#define Header_h

struct DATE {
	int day;
	int month;
	int year;
};

struct INFORM {
	int number;
	double cena;
	int code;
	DATE zakaz;
	DATE vipolnen;
	INFORM* next;
};

struct INFO {
	INFORM* head;
	INFORM* tail;
	unsigned int size = 0;
};

void add(INFO*);
void del(INFO*);
void show(INFORM *data);
void showInfo(INFO*);
void change(INFO*);

void show_1(INFO*);
void show_2(INFO*);
void show_3(INFO*);

#endif
