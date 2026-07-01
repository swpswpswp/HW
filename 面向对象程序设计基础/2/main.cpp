#include <iostream>
using namespace std;
#include "GCD.h"
#include "LCM.h"

int main() {
	int a, b;
	cout << "请输入两个正整数：" << endl;
	cin >> a >> b;
	GCD gcd(a, b);
	LCM lcm(a, b);
	cout << gcd.calculate() << " " << lcm.calculate();
}