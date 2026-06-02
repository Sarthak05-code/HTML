#include <stdio.h>
#include <unistd.h>

#define MEMORY_SIZE 65536
#define CLEAR_SCREEN "\033[H\033[2J"

int main()
{
    fputs(CLEAR_SCREEN, stdout);

    int mem[MEMORY_SIZE];
    
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        mem[i] = i;
        printf("Filling... [%d / %d]\033[K\r", i + 1, MEMORY_SIZE);
        fflush(stdout);
        usleep(100); // 0.1ms per step — adjust to taste
        
    }


    printf("\nMemory filled: all %d slots written.\n", MEMORY_SIZE);
    return 0;
}