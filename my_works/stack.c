#include <stdio.h>
#include "types.h"
#define sysclear "\033[H\033[2J"

int main()
{
    printf(sysclear);
    int n;

    printf("Enter the process time : ");
    scanf("%d", &n);

    int burstTime[n], completedTime[n], turnAround[n], waitingTime[n];
    int time = 0;
    for (int i = 0; i < n; ++i)
    {
        printf("Enter P[%d]: ", i + 1);
        scanf("%d", &burstTime[i]);
    }
    for (size_t i = 0; i < n; i++)
    {
        time += burstTime[i];
        completedTime[i] = time;
    }

    for (size_t i = 0; i < n; i++)
    {
        turnAround[i] = completedTime[i];
        waitingTime[i] = turnAround[i] - burstTime[i];
    }

    printf("Process Time: \t BurstTime: \t TurnAroundTime: \t WaitingTime: \n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n", burstTime[i], completedTime[i], turnAround[i], waitingTime[i]);
    }

    return 0;
}