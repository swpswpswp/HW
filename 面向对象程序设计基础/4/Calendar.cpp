#include <iostream>
using namespace std;
#include "Calendar.h"


void Calendar::set(int year, int month, int day) {
	int Day[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month >= 1 && month <= 12 && day >= 1 && day <= Day[month]) {
		m_year = year;
		m_month = month;
		m_day = day;
	}
	else {
		cout << "输入不合法！" << endl;
	}
}

void Calendar::show() const {
	cout << m_year << "年" << m_month << "月" << m_day << "日" << endl;
}

void Calendar::calculate() {
	int Day[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int n;
	cout << "请输入一个整数：" << endl;
	cin >> n;
	if (n >= 0) {
		for (int i = n;i > 0;i--) {
			m_day++;
			if ((m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0) {
				Day[2] = 29;
			}
			else {
				Day[2] = 28;
			}
			if (m_day == Day[m_month] + 1) {
				m_day = 1;
				m_month++;
			}
			if (m_month == 13) {
				m_month = 1;
				m_year++;
			}
		}
	}
	else {
		for (int i = n;i < 0;i++) {
			m_day--;
			if ((m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0) {
				Day[2] = 29;
			}
			else {
				Day[2] = 28;
			}
			if (m_day == 0) {
				m_month--;
				m_day = Day[m_month];
				
			}
			if (m_month == 0) {
				m_month == 12;
				m_year--;
			}
			if (m_year == 0) {
				m_year--;
			}
		}
	}
	cout << n << "天后是" << m_year << "年" << m_month << "月" << m_day << "日" << endl;
}