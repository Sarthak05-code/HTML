#include <stdio.h>
#include <windows.h>

// File reader tester for the FileTester.txt file, read mode.
int main(void) {
  FILE *f = fopen("Sql.txt", "a");

  if (f == NULL) {
    printf("Error, opening the file.");
    return 1; // exit program
  }

  char input[100];
  printf("Enter something to say here. \n");
  fgets(input, sizeof(input), stdin);
  fputs(input, f);
  fclose(f);
  printf("Written sucessfully.");
  return 0;
}
