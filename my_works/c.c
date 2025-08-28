#include <stdio.h>
#include <string.h>

int main()
{
    char str[50] = "Hello World";
    printf("Length: %lu\n", strlen(str));
    printf("Copy: %s\n", strcpy(str, "Hi!"));
    printf("Concat: %s\n", strcat(str, " How are you?"));
    printf("Compare: %d\n", strcmp("abc", "abd"));
    printf("Find char: %s\n", strchr(str, '!'));
    printf("Find substring: %s\n", strstr(str, "How"));

    return 0;
}
