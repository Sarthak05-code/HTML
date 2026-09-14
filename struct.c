#include <stdio.h>
#include <windows.h>

// File reader tester for the FileTester.txt file, read mode.
int main(void) {
  FILE *fptr = fopen("FileTester.txt", "r");
  char c;
  while (fscanf(fptr, "%c", &c)) {
    printf("%c", c);
    Sleep(10);
  }
  return 0;
}
