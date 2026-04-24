#include <stdio.h>

void f1(int n) {
	int a[11];
	a[0] = 1;
	a[1] = 2;
	for (int i = 2;i < 10;i++) {
		a[i] = 2 * a[i - 1] + a[i - 2];
	}
	printf_s("%d", a[n]);
}
void f2(int n) {
	int a[11];
	a[0] = 0;
	a[1] = 1;
	for (int i = 2;i < 10;i++) {
		a[i] = a[i - 1] + 2 * a[i - 2];
	}
	printf_s("%d", a[n]);
}

int main() {
	void (*p[2])(int) = {f1,f2};
	int n;
	printf_s("#Please enter an integer\n");
	scanf_s("%d", &n);
	p[0](n);
	printf_s(" ");
	p[1](n);
	return 0;
}