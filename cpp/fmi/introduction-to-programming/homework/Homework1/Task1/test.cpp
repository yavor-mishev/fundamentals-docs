#include <stdio.h>

int main()
{
	float a = 0.000001f;
	float b = 1.0f - 0.999999f;
	
	printf("%f\n", a);
	printf("%f\n", b);
	return 0;
}