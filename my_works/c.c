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

void transposeSquare(int array[10][10], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j) // only upper triangle
        {
            int temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }
}

void transposeRectangular(int array[10][10], int trans[10][10], int rows, int cols)
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

    printf("\nOriginal Matrix:\n");
    display(array, rows, cols);

    if (rows == cols) // square matrix
    {
        transposeSquare(array, rows);
        printf("\nTranspose of Square Matrix:\n");
        display(array, rows, cols);
    }
    else // rectangular matrix
    {
        transposeRectangular(array, trans, rows, cols);
        printf("\nTranspose of Rectangular Matrix:\n");
        display(trans, cols, rows); // rows and cols swapped
    }

    return 0;
}
