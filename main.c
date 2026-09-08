#include <stddef.h>
#include <stdio.h>

int main(void) {
  FILE *fptr = fopen("FileTester.txt", "r");
  char c;
  size_t vowel_count = 0;
  size_t conso_count = 0;
  size_t special_count = 0;

  while (fscanf(fptr, "%c", &c) == 1) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
      vowel_count++;
    } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
      conso_count++;
    } else {
      special_count++;
    }
  }
  printf("The amount of vowel are : %zu and the consonent are : %zu and "
         "special character count are : %zu",
         vowel_count, conso_count, special_count);

  return 0;
}
