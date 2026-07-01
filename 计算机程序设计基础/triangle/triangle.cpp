#include <stdio.h>
#include <math.h>

int main() {
	float a, h, S, V;
	printf_s("#请输入一个正三棱柱的底面边长和高：\n");
	scanf_s("%f%f", &a, &h);
	S = sqrt(3) / 4 * a * a * 2 + a * h * 3;
	V = sqrt(3) / 4 * a * a * h;
	printf_s("%4.3f %4.3f", S, V);
	return 0;
}