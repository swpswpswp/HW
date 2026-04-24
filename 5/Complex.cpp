#include <iostream>
using namespace std;
#include "Complex.h"

Complex operator+(const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.m_real = c1.m_real + c2.m_real;
	c3.m_imaginary = c1.m_imaginary + c2.m_imaginary;
	return c3;
}

Complex operator-(const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.m_real = c1.m_real - c2.m_real;
	c3.m_imaginary = c1.m_imaginary - c2.m_imaginary;
	return c3;
}

Complex operator*(const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.m_real = c1.m_real * c2.m_real - c1.m_imaginary * c2.m_imaginary;
	c3.m_imaginary = c1.m_real * c2.m_imaginary + c1.m_imaginary * c2.m_real;
	return c3;
}

Complex operator/(const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.m_real = (c1.m_real * c2.m_real + c1.m_imaginary * c2.m_imaginary) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary);
	c3.m_imaginary = (-c1.m_real * c2.m_imaginary + c1.m_imaginary * c2.m_real) / (c2.m_real * c2.m_real + c2.m_imaginary * c2.m_imaginary);
	return c3;
}

Complex& operator++(Complex& c)
{
	c.m_real++;
	return c;
}

Complex operator++(Complex& c, int)
{
	Complex old = c;
	c.m_real++;
	return old;
}

Complex& operator--(Complex& c)
{
	c.m_real--;
	return c;
}

Complex operator--(Complex& c, int)
{
	Complex old = c;
	c.m_real--;
	return old;
}
