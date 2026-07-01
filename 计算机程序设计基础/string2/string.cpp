#include <stdio.h>
#include <string.h>

int main() {
	char s[101], tmp;
	char* p = s;
	unsigned int m;
	printf_s("#Please enter a string\n");
	gets_s(s);
	printf_s("#Please enter an integer\n");
	scanf_s("%d", &m);
	if (m >= strlen(s)) {
		printf_s("Error: out of length");
	}
	else if (m + 5 >= strlen(s)) {
		for (int i = strlen(s) - 1;i >= m;i--) {
			p = &s[i];
			printf_s("%c", *p);
		}
	}
	else {
		for (int i = m;i <= m + 2;i++) {
			tmp = s[i];
			s[i] = s[2 * m + 5 - i];
			s[2 * m + 5 - i] = tmp;
		}
		printf_s("%s", p);
	}
	return 0;
}