#include <stdio.h>

int main(void) {
  int x = 50;

  int *ptr = &x;

  printf("Address = %p\n", (void *)ptr);
  printf("Value = %d\n", *ptr);

  return 0;
}
