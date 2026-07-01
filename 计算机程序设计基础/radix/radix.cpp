#include <stdio.h>

void fun1_8(int n) {
    int octal[20], i = 0, temp = n;

    while (temp != 0) {
        octal[i++] = temp % 8;
        temp = temp / 8;
    }

    printf("%d 0", n);
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", octal[j]);
    }
    printf("\n");
}

void fun1_16(int n) {
    int hex[20], i = 0, temp = n;
    char hex_digits[] = "0123456789abcdef";

    while (temp != 0) {
        hex[i++] = temp % 16;
        temp = temp / 16;
    }

    printf("%d 0x", n);
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hex_digits[hex[j]]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Please enter a number between 1 and 1000\n");
    scanf_s("%d", &n);

    fun1_8(n);
    fun1_16(n);

    return 0;
}