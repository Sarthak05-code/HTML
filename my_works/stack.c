#include <stdio.h>
#include <stdlib.h>
#define Max 5

int stack[Max];
int top = -1;

void push()
{
    int num;

    if (top == Max - 1)
    {
        printf("The stack is full. \n");
    }
    else
    {
        top++;
        printf("Enter any number: ");
        scanf("%d", &num);
        printf("Number %d has been added to stack: ", num);
        stack[top] = num;
    }
}

void pop()
{
    if (top == -1)
    {
        printf("The stack is empty: \n ");
    }
    else
    {
        printf("Number %d is removed from stack: ", stack[top--]);
    }
}

void display_all()
{
    if (top == -1) // indicates the stack is empty.
    {
        printf("The stack is empty , Hence , no display. \n");
    }

    else
    {
        for (int i = top; i >= 0; --i) // assuming top > -1.
        {
            printf("%d \t", stack[i]);
        }
        printf("\n");
    }
}

void display_top()
{
    if (top == -1)
    {
        printf("The stack is empty , Hence , The stack has no top value: \n");
    }
    else
    {
        printf("The top of the stack value is: %d\n\n", stack[top]);
    }
}

int main(void)
{
    while (1)
    {
        printf("Enter one of the following: ");
        printf("\n1. PUSH: ");
        printf("\n2. POP: ");
        printf("\n3. TRAVERSE: ");
        printf("\n4. Display Top: ");
        printf("\n5. Exit: \n");
        int choice;
        printf("-->> : ");
        scanf("%d", &choice);

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
            printf("Exiting the program. ");
            exit(0);
        default:
            printf("The inpute was incorrect and hence , Enter a new one: ");
            break;
        }
    }
    return 0;
}