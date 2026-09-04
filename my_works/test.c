#include "types.h"
#include <stdint.h>
#include <stdio.h>
typedef uint32_t u32;

int main(void) {
  u32 number = -10;
  if (number > 0)
    printf("The number will hit a buffer underflow");
  else
    printf("The number is : %u \n", number);

  return 0;
}
