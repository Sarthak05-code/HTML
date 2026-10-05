#include <stddef.h>
#include <stdio.h>
#include <synchapi.h>
#include <windows.h>

/***
 * Rust-like loop, this is an infinite loop.
 */
#define loop for (;;)
typedef int Integer;

typedef struct {
  Integer value;
  union {
    double percentage;
  };
} UnionTester;

/***
 * print line with a new line character present.
 */
void println(const char *text) { printf("%s\n", text); }

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

  println("\nHello,world");
  printf("Supposed to see this in a new line.");

  return 0;
}
