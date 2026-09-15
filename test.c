#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int returnNumber() {
    srand(time(NULL));

    return rand() % 10 + 1;
}

