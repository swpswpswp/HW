#include <stdio.h>

int main() {
	float realPart1, realPart2, imaginePart1, imaginePart2, realSum, imagineSum, realDifference, imagineDifference, realProduct, imagineProduct, realQuotient, imagineQuotient;
	printf_s("#请输入两个复数的实部与虚部，用空格隔开：\n");
	scanf_s("%f%f%f%f", &realPart1, &imaginePart1, &realPart2, &imaginePart2);
	realSum = realPart1 + realPart2;
	imagineSum = imaginePart1 + imaginePart2;
	realDifference = realPart1 - realPart2;
	imagineDifference = imaginePart1 - imaginePart2;
	realProduct = realPart1 * realPart2 - imaginePart1 * imaginePart2;
	imagineProduct = realPart1 * imaginePart2 + realPart2 * imaginePart1;
	realQuotient = (realPart1 * realPart2 + imaginePart1 * imaginePart2) / (realPart2 * realPart2 + imaginePart2 * imaginePart2);
	imagineQuotient = (realPart1 * (-imaginePart2) + realPart2 * imaginePart1) / (realPart2 * realPart2 + imaginePart2 * imaginePart2);
	printf_s("%4.3f %4.3f\n%4.3f %4.3f\n%4.3f %4.3f\n%4.3f %4.3f\n", realSum, imagineSum, realDifference, imagineDifference, realProduct, imagineProduct, realQuotient, imagineQuotient);
	return 0;
}