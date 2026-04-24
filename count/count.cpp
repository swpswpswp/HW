#include <stdio.h>

int main() {
    int total_ones = 0;
    int line_count = 0;
    int current_ones = 0;
    int ch;
    long number = 0;
    int has_digits = 0;

    printf_s("#请输入至多5个正整数，用换行隔开\n");

    while (line_count < 5) 
    {
        ch = getchar();

        if (ch == '\n' || ch == EOF) 
        {
            if (has_digits) 
            {
                total_ones += current_ones;
                line_count++;
            }

            number = 0;
            current_ones = 0;
            has_digits = 0;

            if (ch == EOF) break;
            continue;
        }

        if (ch >= '0' && ch <= '9') 
        {
            has_digits = 1;
            number = number * 10 + (ch - '0');
            if (ch == '1') 
            {
                current_ones++;
            }
        }
        else
        {
            printf("Error");
            return 0;
        }
    }

    if (line_count == 0 || total_ones == 0) 
    {
        printf("Error");
    }
    else 
    {
        printf("%d", total_ones);
    }

    return 0;
}