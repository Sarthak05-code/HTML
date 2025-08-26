#include <stdio.h>

int main()
{
    FILE *fptr, *transfer;
    int i, count = 0;

    // Step 1: write numbers 1–100 to example.dat
    fptr = fopen("example.dat", "w");
    if (!fptr)
    {
        printf("Error opening example.dat for writing.\n");
        return 1;
    }
    for (i = 1; i <= 100; i++)
    {
        fprintf(fptr, "%d\t", i);
    }
    fclose(fptr);

    // Step 2: read from example.dat and write evens to even.dat
    fptr = fopen("example.dat", "r");
    transfer = fopen("even.dat", "w");
    if (!fptr || !transfer)
    {
        printf("Error opening file.\n");
        if (fptr)
            fclose(fptr);
        if (transfer)
            fclose(transfer);
        return 1;
    }

    while (fscanf(fptr, "%d", &i) == 1)
    {
        if (i % 2 == 0)
        {
            fprintf(transfer, "%d\t", i);
            count++;
        }
    }

    fclose(fptr);
    fclose(transfer);

    // Step 3: report count (no need to reopen even.dat)
    printf("There are %d values in file even.dat\n", count);
    printf("Even numbers copied successfully.\n");

    return 0;
}
