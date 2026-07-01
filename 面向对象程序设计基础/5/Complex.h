#pragma once
#include <iostream>
class Complex {
public:
	double m_real;
	double m_imaginary;
	Complex(double r = 0, double i = 0) :m_real(r), m_imaginary(i) {}
	void mb_show(const char* s) {
		cout << s << m_real << "+" << m_imaginary << "i" << endl;
	}
};

extern Complex operator + (const Complex& c1, const Complex& c2);
extern Complex operator - (const Complex& c1, const Complex& c2);
extern Complex operator * (const Complex& c1, const Complex& c2);
extern Complex operator / (const Complex& c1, const Complex& c2);
extern Complex& operator ++ (Complex& c);
extern Complex operator ++ (Complex& c, int);
extern Complex& operator -- (Complex& c);
extern Complex operator -- (Complex& c, int);