#include <stdio.h>
#include <math.h>

int main()
{
    double x = 0, y = 0;
    double result = 0;
    scanf("%lf%lf", &x, &y);
    if (x - y == 0)
        printf("Khong tinh duoc!");
    else
    {
        result = (2 * pow((x + y), 3) + pow(63, 4.0 / 5)) / (x - y);
        printf("%lf", result);
    }
    return 0;
}