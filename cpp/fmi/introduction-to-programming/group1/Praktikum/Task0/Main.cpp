#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    float r;
    float x, y;

    printf("Enter radius: ");
    scanf("%f", &r);

    printf("Enter x and y coordinates: ");
    scanf("%f%f", &x, &y);

    float squaredDistance = (x * x + y * y);

    printf("%d", r * r < squaredDistance);
}