#include <iostream>
using namespace std;
#include "GCD.h"

GCD::GCD(int a, int b) :m_a(a), m_b(b) {}

int GCD::calculate() {
	while (1) {
		if (m_a >= m_b) {
			m_a = m_a % m_b;
		}
		else {
			m_b = m_b % m_a;
		}
		if (m_a == 0) {
			return m_b;
		}
		if (m_b == 0) {
			return m_a;
		}
	}
}