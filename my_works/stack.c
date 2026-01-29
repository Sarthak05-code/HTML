#include <stdio.h>
#include <unistd.h>

int main()
{
    int hour, minute, second;

    printf("Enter timer\n");
    printf("Hour   : ");
    scanf("%d", &hour);
    printf("Minute : ");
    scanf("%d", &minute);
    printf("Second : ");
    scanf("%d", &second);

    // Input validation
    if (hour < 0 || minute < 0 || minute > 59 || second < 0 || second > 59)
    {
        printf("Invalid time input!\n");
        return 1;
    }

    int totalSeconds = hour * 3600 + minute * 60 + second;

    while (totalSeconds >= 0)
    {
        int h = totalSeconds / 3600;
        int m = (totalSeconds % 3600) / 60;
        int s = totalSeconds % 60;

        printf("%02d : %02d : %02d\r", h, m, s);
        fflush(stdout);

        sleep(1);
        totalSeconds--;
    }

    printf("\nTime over!\n");
    return 0;
}
