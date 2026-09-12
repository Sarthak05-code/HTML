#include <stdio.h>
#define mod %
#define foreach(arr, i, n) for (int i = 0; i < (n); ++i)

int len(int array[]) { return sizeof(array) / sizeof(array[0]); }

int main(void) {

  int number = 10;

  if (number mod 2 == 0)
    printf("Number is even.\n");
  else
    printf("The number is odd.\n");

  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int length = sizeof(array) / sizeof(array[0]);

  foreach (array, i, length) {
    printf("%d\t", i);
  };

  int size = len(array);
  printf("The size is : %d\n", size);
  return 0;
}
