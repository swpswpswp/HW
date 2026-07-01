#include <stdio.h>
#include <string.h>

char s[101][101], temp[101];

void refresh(char* m[]) {
	for (int i = 0;i < 100;i++) {
		m[i] = s[i];
	}
}
void divide_into(char temp[], char* m[]) {
	int count = 0;
	for (int i = 0;i < strlen(temp);i++) {
		if (temp[i] == ' ') {
			count++;
			continue;
		}
		else {
			*m[count] = temp[i];
			m[count]++;
		}
	}
	refresh(m);
}

int main() {
	char* m[101];
	int n;
	refresh(m);
	printf_s("#Please enter a sentence:\n");
	gets_s(temp);
	divide_into(temp, m);

	for (int i = 99;i >= 0;i--) {
		*m[i] -= 32;
		printf_s("%s ", m[i]);
	}
	return 0;
}