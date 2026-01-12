#include <stdio.h>
#include "types.h"


int main(void){
    u32 a;
    b32 b;
    printf("Enter a: ");
    scanf("%u",&a);
    printf("%u", a);

     b = isEven(a);
    printf("\n%d", b);

    printf("\nEnter a number for factorial: ");
    u32 c;
    scanf("%d", &c);

    printf("The factorial of %d is %u", c , factorial(c));

    

    return 0;
}