#include <stdio.h>
int main()
{
	int n;
	float money;
	printf_s("#请输入一个1至500范围内的整型数，代表购买数量\n");
	scanf_s("%d", &n);
	if (n <= 0 || n > 500)
	{
		printf_s("Error");
		return 0;
	}
	else if (n <= 5)
	{
		money = n * 10.0 * (1.0 - (n - 1.0) / 100.0);
	}
	else if (n <= 20)
	{
		money = n * 10.0 * (1.0 - (4.0 + (n - 5.0) * 0.4) / 100.0);
	}
	else if (n <= 50)
	{
		money = n * 10.0 * (1.0 - (10.0 + (n - 20.0) * 0.15) / 100.0);
	}
	else if (n <= 300)
	{
		money = n * 10.0 * (1.0 - (14.5 + (n - 50.0) * 0.03) / 100.0);
	}
	else
	{
		money = n * 10.0 * (1.0 - 22.0 / 100.0);
	}
	printf_s("%10.3f", money);
	return 0;
}