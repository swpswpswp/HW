#include <stdio.h>
#include <string.h>

void fun3() {
	char s[101];
	gets_s(s);
	bool is = 0;
	for (int i = 0;i < strlen(s);i++) {
		if (s[i] == 'i' && s[i + 1] == 's') {
			s[i] = 'b';
			s[i + 1] = 'e';
			is = 1;
		}
	}
	if (is == 0) {
		printf_s("Error");
	}
	else {
		printf_s("%s", s);
	}
}

int main() {
	fun3();
	return 0;
}