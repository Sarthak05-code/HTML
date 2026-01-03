#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

/* Insert at end */
void Insert(int value)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = value;
    ptr->next = NULL;

    if (head == NULL)
    {
        head = ptr;
    }
    else
    {
        struct Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = ptr;
    }

    printf("Inserted %d into the list\n", value);
}

/* Delete a specific value */
void Delete(int value)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    /* If head needs to be deleted */
    if (temp->data == value)
    {
        head = temp->next;
        free(temp);
        printf("Deleted %d from the list\n", value);
        return;
    }

    while (temp != NULL && temp->data != value)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted %d from the list\n", value);
}

/* Display first node */
void displayFront()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    printf("First element: %d\n", head->data);
}

/* Traverse the list */
void Traverse()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;
    printf("Linked List: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    int choice, value;

    printf("-----Menu-----\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display First\n");
    printf("4. Traverse\n");
    printf("5. Exit\n");

    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            Insert(value);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            Delete(value);
            break;

        case 3:
            displayFront();
            break;

        case 4:
            Traverse();
            break;

        case 5:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }

    } while (1);

    return 0;
}
