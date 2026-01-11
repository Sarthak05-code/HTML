#include <stdio.h>
#include <string.h>

int main(void){
    char binary[32];
    int num = 0;
    int lenght;
    printf("Enter a binary: ");
    scanf("%s",binary);
    lenght = strlen(binary);

    for(int i = 0 ; i < lenght ; ++i){
        if(binary[i] != '0' && binary[i] != '1'){
            printf("Invalid Entry");
            return 1;

        }

        int bit = binary[i] - '0';

        num = num * 2 + bit;
    }

    printf("The number is: %d" , num);
    return 0;
}