#include <stdio.h>

void fun2() {
	char s[101];
	static bool a[101];
	gets_s(s);
	int i = 0, j = 0, max_length = 0, sum = 0;
	static int count[101];
	while (s[i] != '\0') {
		if (s[i] == ' ') {
			j++;
			i++;
			continue;
		}
		if (s[i] == 'a' || s[i] == 'A') {
			a[j] = 1;
		}
		i++;
		count[j]++;
	}
	for (int i = 0;i <= j;i++) {
		if (a[i] == 1 && max_length < count[i]) {
			max_length = count[i];
		}
	}
	for (int i = 0;i <= j;i++) {
		if (a[i] == 1 && count[i] == max_length) {
			for (int k = 0;k < i;k++) {
				sum += count[k];
			}
			for (int k = sum + i;k < sum + i + count[i];k++) {
				printf_s("%c", s[k]);
			}
		}
	}
	if (max_length == 0) {
		printf_s("Error");
	}
}

int main() {
	fun2();
	return 0;
}