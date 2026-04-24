#pragma once
class Calendar {
private:
	int m_year, m_month, m_day;
public:
	Calendar() :m_year(1), m_month(1), m_day(1){}
	~Calendar(){}
	void set(int year,int month,int day);
	void show() const;
	void calculate();
};
