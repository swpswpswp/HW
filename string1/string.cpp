#include <stdio.h>
#include <string.h>

int main() {
	char s[101];
	printf_s("#Please enter a string:\n");
	scanf_s("%s", s, 100);
	char* m = s;
	int n1 = 0, n2 = 0;
	for (int i = 0;i < strlen(s);i++) {
		if (*m >= 48 && *m <= 57) {
			n1++;
		}
		else if (*m >= 101 && *m <= 107) {
			n2++;
		}
		m++;
	}
	printf_s("%d %d", n1, n2);
	return 0;
}