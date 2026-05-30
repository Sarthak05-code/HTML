#include <stdio.h>
#include <math.h>

#define e 0.00001

double function(double x) {
    return (pow(x, 4) - x - 10);
}

double function_derivative(double x) {
    return (4 * pow(x, 3) - 1);
}

int main() {
    double x, xn, prev;
    int i = 0;

    printf("Enter initial guess: ");
    scanf("%lf", &x);

    printf("Iter | x_n\n");

    for (;;) {
        double d = function_derivative(x);

        if (d == 0) {
            printf("Derivative zero, stopping.\n");
            break;
        }

        xn = x - function(x) / d;

        printf("%d | %lf\n", i, xn);

        if (fabs(xn - x) < e) {
            printf("Root found: %lf\n", xn);
            break;
        }

        x = xn;
        i++;

        if (i > 20) {
            printf("Did not converge.\n");
            break;
        }
    }

    return 0;
}