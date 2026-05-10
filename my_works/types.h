#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

// ===== Basic Types =====
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef bool b32;

// ===== Utility Functions =====

// Check even number
static inline b32 isEven(s32 n)
{
    return (n % 2 == 0);
}

// Factorial
static inline u32 factorial(u32 n)
{
    u32 result = 1;
    for (u32 i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

// Print array
static inline void arrayPrinter(const u32 *array, u32 n)
{
    for (u32 i = 0; i < n; i++)
    {
        printf("%u\t", array[i]);
    }
    printf("\n");
}

typedef struct
{
    int x;
    int y;
} Vec2;

typedef struct
{
    int x, y, z;
} Vec3;

#endif