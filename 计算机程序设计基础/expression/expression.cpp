#include <stdio.h>
int main() {
	int n;
	float exp = 0.0;
	printf_s("#请输入一个0到100之间的正整数\n");
	scanf_s("%d", &n);
	for (int i = 1;i <= n;i++) {
		exp += (i * i / (i + 1.0));
	}
	printf_s("%10.3f", exp);
	return 0;
}