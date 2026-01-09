#include <stdio.h>

int main(void)
{
    int array[100]; // Declaring an array that store upto a hundred number.
    int i = 0;
    while (1) // while true will make sure the loop runs nonstop
    {
        if (i >= 100)
        {
            printf("Overflowed array , exiting the program.");
            break;
        }
        printf("Enter a number: ");
        scanf("%d", &array[i]);
        if (array[i] < 0) // check if negative number.
        {
            printf("Negative number scanned , terminating the program. ");
            break;
        }

        i++; // move the index
    }

    printf("The number is reverse order: \n");
    for(int j = i -1 ; j >= 0 ; --j) // last incremented number of i
    {
        printf("%d\t", array[j]);
    }

    return 0;
}