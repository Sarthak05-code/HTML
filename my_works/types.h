#ifndef TYPES_DATA_TYPES
#define TYPES_DATA_TYPES
typedef unsigned int u32;
typedef int b32;
typedef float f32;
typedef signed int s32;

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

static inline b32 isEven(int n)
{
    return (n % 2 == 0);
}

static inline u32 factorial(u32 n)
{
    u32 result = 1;
    for (u32 i = 1; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}
static inline u32 arrayPrinter(const u32 *array, u32 n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%u\t", *(array + i));
    }
}

#endif