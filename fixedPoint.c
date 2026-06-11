#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001

double g(double x) {
    return exp(-x);
}

double f(double x) {
    return exp(-x) - x;
}

int main() {

    double x0, x;
    int i, MAX = 100;

    printf("Enter initial guess: ");
    scanf("%lf", &x0);

    for(i = 0; i < MAX; i++) {

        x = g(x0);

        printf("Iteration %2d | x = %.8lf | f(x) = %.8lf\n",
               i + 1, x, f(x));

        if(fabs(x - x0) < EPSILON) {
            printf("\nConverged at %.8lf after %d iterations\n",
                   x, i + 1);
            return 0;
        }

        x0 = x;
    }

    printf("\nFailed to converge within %d iterations\n", MAX);

    return 0;
}