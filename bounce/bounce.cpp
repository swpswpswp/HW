#include <stdio.h>
int main() {
	int n;
	float h = 100.0;
	printf_s("#请输入一个1到1000之间的正整数\n");
	scanf_s("%d", &n);
	for (int i = 1;i <= n;i++) {
		h *= (2.0 / 3.0);
	}
	if (h >= 1.0) {
		printf_s("%10.3f", h);
	}
	else {
		printf_s("No Bounce");
	}
	return 0;
}