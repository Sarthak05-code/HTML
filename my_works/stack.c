#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};

struct Node *last = NULL;



void insert(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    
    if (last == NULL) {
        newNode->next = newNode;
        last = newNode;
    } else {
        newNode->next = last->next;
        last->next = newNode;
        last = newNode;
    }
    printf("Inserted %d\n", value);
}

void delete() {
    if (last == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node *front = last->next;
    if (front == last) {
        printf("Deleted %d\n", front->data);
        free(front);
        last = NULL;
    } else {
        printf("Deleted %d\n", front->data);
        last->next = front->next;
        free(front);
    }
}

void displayFront() {
    if (last == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Front element: %d\n", last->next->data);
}

void traverse() {
    if (last == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node *temp = last->next;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != last->next);
    printf("\n");
}

int main(void) {
    int choice, value;
    
    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display Front\n4. Traverse\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                delete();
                break;
            case 3:
                displayFront();
                break;
            case 4:
                traverse();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}