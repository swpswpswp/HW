#include <stdio.h>

int main() {
	int day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	struct date {
		int year;
		int month;
		int day;
	};
	typedef struct date DATE;
	DATE a, b;
	scanf_s("%d%d%d", &a.year, &a.month, &a.day);
	scanf_s("%d%d%d", &b.year, &b.month, &b.day);
	for (i = 0;!(a.year == b.year && a.month == b.month && a.day == b.day);i++) {
		if (a.year == 2020 || a.year == 2024) {
			day[2] = 29;
		}
		else {
			day[2] = 28;
		}
		if (a.day == day[a.month]) {
			a.day = 0;
			a.month++;
		}
		a.day++;
		if (a.month == 13) {
			a.month = 1;
			a.year++;
		}
	}
	printf_s("%d", i);
	return 0;
}