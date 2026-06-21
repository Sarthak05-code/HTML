#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include "types.h"

#define sysclear "\033[H\033[2J"
#define BOUND 10.0
 
// Random float between min and max
static inline f64 randRange(f64 min, f64 max)
{
    return min + ((f64)rand() / RAND_MAX) * (max - min);
}

int main()
{
    printf(sysclear);
    srand((unsigned int)time(NULL));  // seed once — crucial!

    Vec2 p  = {0.0, 0.0};
    Vec2 p2 = {5.0, 3.0};

    for (u32 i = 0; i < 25; i++)
    {
        // Random step each iteration
        p.x  += randRange(0.5, 3.0);
        p.y  += randRange(0.5, 3.0);
        p2.x += randRange(0.3, 2.0);
        p2.y += randRange(0.3, 2.0);

        // Wrap
        if (p.x  > BOUND) p.x  = 0;
        if (p.y  > BOUND) p.y  = 0;
        if (p2.x > BOUND) p2.x = 0;
        if (p2.y > BOUND) p2.y = 0;

        printf("Iter %2u | P1: %6.2f %6.2f  |  P2: %6.2f %6.2f\n",
               i + 1, p.x, p.y, p2.x, p2.y);
    }

    return 0;
}