#include <stdio.h>  
#include<string.h>



int main(void) {
    char name[100];

    printf("Enter a word: ");
    fgets(name , sizeof(name) , stdin);

    int i = 0;

    int size = 0;


    for (size_t i = 0; name[i] != '\0'; i++)
    {
        size++;
    }
    size  = size - 1;

    int n = 0;

    while (n < size)
    {
        
    }
    
    return 0;
}