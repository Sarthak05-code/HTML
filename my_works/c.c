#include <stdio.h>

#define maxsubjects 5

typedef struct
{
    char name[50];
    char id[50];
    int age;
    float grades[maxsubjects];
} records;

int main(void)
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    records class[n];

    // Define subject names
    char subjects[maxsubjects][50] = {"Math-2", "C-program", "Micro-Processor", "Eng-2", "Accounting"};

    // Input student info and grades
    for (int i = 0; i < n; ++i)
    {
        printf("\n--- Student %d ---\n", i + 1);

        printf("Enter name: ");
        scanf("%49s", class[i].name);

        printf("Enter ID: ");
        scanf("%49s", class[i].id);

        printf("Enter age: ");
        scanf("%d", &class[i].age);

        // Input grades
        for (int j = 0; j < maxsubjects; ++j)
        {
            printf("Enter grade for %s in %s: ", class[i].name, subjects[j]);
            scanf("%f", &class[i].grades[j]);

            // Punish overflow grades
            if (class[i].grades[j] > 100)
            {
                class[i].grades[j] -= 100;
                printf("Oops, grade adjusted to %.2f \n", class[i].grades[j]);
            }
        }
    }

    // Display all students with their grades and highlight failures
    printf("\n\n--- Student Records ---\n");
    for (int i = 0; i < n; ++i)
    {
        printf("\nStudent %d: %s | ID: %s | Age: %d\n", i + 1, class[i].name, class[i].id, class[i].age);

        int failed = 0; // flag for failure
        for (int j = 0; j < maxsubjects; ++j)
        {
            printf("%s: %.2f", subjects[j], class[i].grades[j]);
            if (class[i].grades[j] < 40) // assuming 40 is passing mark
            {
                printf("  <-- FAILED");
                failed = 1;
            }
            printf("\n");
        }

        if (failed)
        {
            printf("Notice: %s has failed in one or more subjects!\n", class[i].name);
        }
        else
        {
            printf("%s passed all subjects.\n", class[i].name);
        }
    }

    printf("\nEnded\n");
    return 0;
}
