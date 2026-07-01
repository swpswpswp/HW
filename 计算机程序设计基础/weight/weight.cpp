#include <stdio.h>
int main() {
	int n, count = 0;
	printf_s("#请输入一个0到100之间的正整数\n");
	scanf_s("%d", &n);
	for (int i = 0;i <= 20;i++) {
		for (int j = 0;j <= 50 - 2.5 * i;j++) {
			if((5*i+2*j+(n-i-j))==100){
				count++;
			}
		}
	}
	printf_s("%d", count);
	return 0;
}