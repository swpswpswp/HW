#include <stdio.h>
int main()
{
	float a, b, c, d, max;
	printf_s("#请输入四个实型数，绝对值不超过1000\n");
	scanf_s("%f%f%f%f", &a, &b, &c, &d);
	if (a == 0.0 && b == 0.0 && c == 0.0 && d == 0.0) //情形1
	{
		printf_s("Exit");
	}
	else if (a == b || a == c || a == d || b == c || b == d || c == d) //情形2
	{
		printf_s("Error:Equal");
	}
	else if (a > 1000.0 || a < -1000.0 || b > 1000.0 || b < -1000.0 || c > 1000.0 || c < -1000.0 || d > 1000.0 || d < -1000.0) //情形3
	{
		printf_s("Error:Out of Range");
	}
	else //情形4 找最大值
	{
		max = a;
		if (max < b)
		{
			max = b;
		}
		if (max < c)
		{
			max = c;
		}
		if (max < d)
		{
			max = d;
		}
		printf_s("%10.3f", max);
	}
	return 0;
}