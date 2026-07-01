#include <iostream>
using namespace std;
#include "ComplexTest.h"

void ComplexTest()
{
	while (1) {
		string c;
		cout << "请输入想测试的运算符，测试完毕请输入0：" << endl;
		cin >> c;
		if (c == "+") {
			double m1, i1, m2, i2;
			cout << "请输入第一个复数的实部、虚部：" << endl;
			cin >> m1 >> i1;
			cout << "请输入第二个复数的实部、虚部：" << endl;
			cin >> m2 >> i2;
			Complex c1(m1, i1), c2(m2, i2), c3 = c1 + c2;
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			c3.mb_show("c1+c2=");
		}
		else if (c == "-") {
			double m1, i1, m2, i2;
			cout << "请输入第一个复数的实部、虚部：" << endl;
			cin >> m1 >> i1;
			cout << "请输入第二个复数的实部、虚部：" << endl;
			cin >> m2 >> i2;
			Complex c1(m1, i1), c2(m2, i2), c3 = c1 - c2;
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			c3.mb_show("c1-c2=");
		}
		else if (c == "*") {
			double m1, i1, m2, i2;
			cout << "请输入第一个复数的实部、虚部：" << endl;
			cin >> m1 >> i1;
			cout << "请输入第二个复数的实部、虚部：" << endl;
			cin >> m2 >> i2;
			Complex c1(m1, i1), c2(m2, i2), c3 = c1 * c2;
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			c3.mb_show("c1*c2=");
		}
		else if (c == "/") {
			double m1, i1, m2, i2;
			cout << "请输入第一个复数的实部、虚部：" << endl;
			cin >> m1 >> i1;
			cout << "请输入第二个复数的实部、虚部：" << endl;
			cin >> m2 >> i2;
			Complex c1(m1, i1), c2(m2, i2), c3 = c1 / c2;
			c1.mb_show("c1=");
			c2.mb_show("c2=");
			c3.mb_show("c1/c2=");
		}
		else if (c == "++") {
			int a;
			cout << "前++请输入1，后++请输入0：" << endl;
			cin >> a;
			if (a == 1) {
				double m, i;
				cout << "请输入复数的实部、虚部：" << endl;
				cin >> m >> i;
				Complex c(m, i);
				c.mb_show("c=");
				Complex c_new = ++c;
				c_new.mb_show("++c=");
				c.mb_show("c=");
			}
			else {
				double m, i;
				cout << "请输入复数的实部、虚部：" << endl;
				cin >> m >> i;
				Complex c(m, i);
				c.mb_show("c=");
				Complex c_new = c++;
				c_new.mb_show("c++=");
				c.mb_show("c=");
			}
		}
		else if (c == "--") {
			int a;
			cout << "前--请输入1，后--请输入0：" << endl;
			cin >> a;
			if (a == 1) {
				double m, i;
				cout << "请输入复数的实部、虚部：" << endl;
				cin >> m >> i;
				Complex c(m, i);
				c.mb_show("c=");
				Complex c_new = --c;
				c_new.mb_show("--c=");
				c.mb_show("c=");
			}
			else {
				double m, i;
				cout << "请输入复数的实部、虚部：" << endl;
				cin >> m >> i;
				Complex c(m, i);
				c.mb_show("c=");
				Complex c_new = c--;
				c_new.mb_show("c--=");
				c.mb_show("c=");
			}
		}
		else if (c == "0") {
			break;
		}
	}
}
