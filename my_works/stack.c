#include <fcntl.h>
#include "types.h"
#include <stdio.h>
#include <unistd.h>



int main(int argc, char const *argv[])
{
    int n = 5;
    int array[] = {1,2,3,4,5,6};

    arrayPrinter(array , n);
    return 0;
}
