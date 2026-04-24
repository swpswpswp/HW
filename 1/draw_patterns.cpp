#include <iostream>
using namespace std;
#include "draw_patterns.h"

void draw_patterns::mb_draw() {
	for (int i = 0;i < m_h;i++) {
		for (int j = 0;j <= i;j++) {
			cout << m_char;
		}
		cout << endl;
	}
}

void draw_patterns::mb_input() {
	cout << "请输入塔的高度和填充的字符：" << endl;
	cin >> m_h >> m_char;
}