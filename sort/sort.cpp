#include <stdio.h>
#include <string.h>

int main() {
	char s[101];
	char temp;
	int count = 0, k = 0;
	printf_s("请输入一个字符串，长度不大于100\n");
	gets_s(s);
	_strupr_s(s);
	for (int i = 0;i < strlen(s) - count;i++) {
		if (!((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 90))) {
			temp = s[strlen(s) - count - 1];
			s[strlen(s) - count - 1] = s[i];
			s[i] = temp;
			count++;
		}
	}
	for(int i = 0;i < strlen(s) - count;i++){
		for (int j = 0;j < strlen(s) - count - i - 1;j++) {
			if (s[j] > s[j + 1]) {
				temp = s[j + 1];
				s[j + 1] = s[j];
				s[j] = temp;
			}
		}
	}
	for (int i = 0;i < strlen(s) - count;i++) {
		if (s[i] == s[i + 1]) {
			continue;
		}
		printf_s("%c\n", s[i]);
	}
	return 0;
}