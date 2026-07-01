#include <stdio.h>
#include <stdlib.h>

int main() {
	int m, n, * p1, * p2, i, j, * p;
	printf_s("#Please enter 2 integers:\n");
	scanf_s("%d%d", &n, &m);
	p1 = (int*)malloc(n * sizeof(int));
	p2 = (int*)malloc(m * sizeof(int));
	p = (int*)malloc((n + m) * sizeof(int));
	printf_s("#Please enter %d integers:\n", n);
	for (int i = 0;i < n;i++) {
		scanf_s("%d", p1);
		p1++;
	}
	printf_s("#Please enter %d integers:\n", m);
	for (int i = 0;i < m;i++) {
		scanf_s("%d", p2);
		p2++;
	}
	p1 -= n;
	p2 -= m;
	i = 0;
	j = 0;
	while (i < n && j < m) {
		if (*p1 <= *p2) {
			*p = *p1;
			p1++;
			i++;
		}
		else {
			*p = *p2;
			p2++;
			j++;
		}
		p++;
	}
	if (i == n) {
		while (j < m) {
			*p = *p2;
			p2++;
			j++;
			p++;
		}
	}
	else {
		while (i < n) {
			*p = *p1;
			p1++;
			i++;
			p++;
		}
	}
	p -= (m + n);
	for (int i = 0;i < m + n;i++) {
		printf_s("%d ", *p);
		p++;
	}
	return 0;
}