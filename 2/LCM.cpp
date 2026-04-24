#include <iostream>
using namespace std;
#include "LCM.h"

LCM::LCM(int a, int b) :m_a(a), m_b(b), m_gcd(1) {}

int LCM::calculate() {
	int a = m_a, b = m_b;
	while (1) {
		if (m_a >= m_b) {
			m_a = m_a % m_b;
		}
		else {
			m_b = m_b % m_a;
		}
		if (m_a == 0) {
			m_gcd = m_b;
			break;
		}
		if (m_b == 0) {
			m_gcd = m_a;
			break;
		}
	}
	return a * b / m_gcd;
}
