#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define final const
#define sysclear "\033[H\033[2J"

typedef struct
{
    int critValue[10];
} storage;

int main()
{
    printf(sysclear);

    storage s;
    srand(time(NULL));

    final int critRate = 75;

    for (int i = 0; i < 10; ++i)
    {
        s.critValue[i] = (rand() % 100) + 1;
        printf("Crit Value: %d\n", s.critValue[i]);
    }

    return 0;
}