#include <stdio.h>
#include <string.h>

struct string {
	int len;
	int space;
	int letter;
	int number;
};
typedef struct string STR;

void string_compare(STR str1, STR str2) {
	printf_s("%d %d %d %d", str1.len == str2.len, str1.space == str2.space, str1.letter == str2.letter, str1.number == str2.number);
}

int main() {
	static STR str1, str2;
	char s1[101], s2[101];
	gets_s(s1);
	rewind(stdin);
	gets_s(s2);
	str1.len = strlen(s1);
	str2.len = strlen(s2);
	for (int i = 0;i < strlen(s1);i++) {
		if (s1[i] == ' ') {
			str1.space++;
		}
		else if (s1[i] >= 48 && s1[i] <= 57) {
			str1.number++;
		}
		else if (s1[i] >= 65 && s1[i] <= 90 || s1[i] >= 97 && s1[i] <= 122) {
			str1.letter++;
		}
	}
	for (int i = 0;i < strlen(s2);i++) {
		if (s2[i] == ' ') {
			str2.space++;
		}
		else if (s2[i] >= 48 && s2[i] <= 57) {
			str2.number++;
		}
		else if (s2[i] >= 65 && s2[i] <= 90 || s2[i] >= 97 && s2[i] <= 122) {
			str2.letter++;
		}
	}
	string_compare(str1, str2);
	return 0;
}