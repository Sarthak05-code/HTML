#include <stdio.h>

void display(int array[10][10], int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%d \t", array[i][j]);
        }
        printf("\n");
    }
}

void transpose(int array[10][10], int trans[10][10], int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            trans[j][i] = array[i][j]; // put row into column
        }
    }
}

int main()
{
    int array[10][10], trans[10][10];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    // input
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &array[i][j]);
        }
    }

    printf("Original Matrix:\n");
    display(array, rows, cols);

    // transpose
    transpose(array, trans, rows, cols);

    printf("Transpose of the Matrix:\n");
    display(trans, cols, rows); // note: rows and cols are swapped here

    return 0;
}
