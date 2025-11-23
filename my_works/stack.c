#include <stdio.h>
#include <stdlib.h>

#define Max 5

int stack[Max];
int top = -1;

void push(void)
{
    int num;

    if (top == Max - 1)
    {
        printf("The stack is full.\n");
    }
    else
    {
        top++;
        printf("Enter any number: ");
        if (scanf("%d", &num) == 1)
        {
            stack[top] = num;
            printf("Number %d has been added to the stack.\n\n", num);
        }
        else
        {
            /* consume invalid input */
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Invalid input. No number was added.\n\n");
            top--;
        }
    }
}

void pop(void)
{
    if (top == -1)
    {
        printf("The stack is empty.\n");
    }
    else
    {
        printf("Number %d is removed from the stack.\n", stack[top--]);
    }
}

void display_all(void)
{
    if (top == -1)
    {
        printf("The stack is empty; nothing to display.\n");
    }
    else
    {
        for (int i = top; i >= 0; --i)
        {
            printf("--> %d\n", stack[i]);
        }
    }
}

void display_top(void)
{
    if (top == -1)
    {
        printf("The stack is empty; there is no top value.\n");
    }
    else
    {
        printf("The top of the stack is: %d\n\n", stack[top]);
    }
}

int main(void)
{
    while (1)
    {
        printf("Enter one of the following:");
        printf("\n1. PUSH");
        printf("\n2. POP");
        printf("\n3. TRAVERSE");
        printf("\n4. Display Top");
        printf("\n5. Exit\n");

        int choice;
        printf("-->> ");
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Invalid choice. Please enter a number between 1 and 5.\n\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            display_all();
            break;
        case 4:
            display_top();
            break;
        case 5:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("The input was incorrect; enter a new one.\n");
            break;
        }
    }

    return 0;
}