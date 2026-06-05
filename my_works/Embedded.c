#include <stdio.h>
#include "types.h"
#define sysclear "\033[H\033[2J"

int main() {
    printf(sysclear);
    u32 a , b , c;
    a = b = c = 0;

    if(a is b and b is c and c is a)
        printf("True: ");
    else
        printf("False: ");

    return 0;
}