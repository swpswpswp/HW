#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* f[11];
	FILE* fp;
	if (fopen_s(&fp, "grade.in","r") != 0) {
		printf_s("This file can¡¯t be opened!\n");
		return 0;
	}
	int i = 0, count = 0;
	while (fgets(f[i], 100, fp) != 0) {
		i++;
		count++;
	}
	for (int i = 0;i < count;i++) {
		for (int j = 0;j < strlen(f[i]);j++) {
			if (*f[i] == 'e' && *(f[i] + 3) == '8') {
				f[i] -= j;
				printf_s("%s", f[i]);
				break;
			}
			f[i]++;
		}
	}
	return 0;
}