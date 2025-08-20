#include <stdio.h>

int binarysearch(int array[], int n, int target)
{
    int mid, l, r;
    l = 0;
    r = n - 1;
    while (l <= r)
    {
        mid = (l + r) / 2;

        if (array[mid] == target)
        {
            return mid;
        }
        else if (array[mid] > target)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int array[100];
    int i, n;
    printf("Enter N: ");
    scanf("%d", &n);

    for (i = 0; i < n; ++i)
    {
        printf("a[%d] = ", i);
        scanf("%d", &array[i]);
    }
    int target;
    printf("Enter the number: ");
    scanf("%d", &target);

    int index = binarysearch(array, n, target);
    if (index != -1)
    {
        printf("The index is %d", index);
    }
    else
        printf("The index wasnt found!");

    return 0;
}