#include <stdio.h>
#include <math.h>

#define sysclear "\033[H\033[2J"
#define e 0.000001

double f(double x)
{
    return x * x * x - x - 2;
}

int main()
{
    printf(sysclear);
    double x0, x1, x2, Fx2;
    int MAX_I = 100, i = 0;

    printf("Enter x0 and x1: ");
    scanf("%lf %lf", &x0, &x1);

    if (f(x0) * f(x1) >= 0)
    {
        printf("Invalid choice\n");
        return 1;
    }

    printf("Iter\t\tx0\t\tx1\t\tx2\t\tF(x2)\n");
    printf("----\t\t--\t\t--\t\t--\t\t-----\n");

    do
    {
        x2  = (x0 * f(x1) - x1 * f(x0)) / (f(x1) - f(x0));
        Fx2 = f(x2);

        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\n", i + 1, x0, x1, x2, Fx2);

        if (Fx2 == 0)
            break;
        else if (f(x0) * Fx2 < 0)
            x1 = x2;
        else
            x0 = x2;

        i++;

    } while (fabs(Fx2) > e && i < MAX_I);

    printf("\nThe root of the equation is: %.6lf\n", x2);
    return 0;
}