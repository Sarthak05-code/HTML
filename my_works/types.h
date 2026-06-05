#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ===== Basic Types =====
typedef uint32_t u32; // unsigned 32 bit integer
typedef int32_t s32;  // signed 32 bit integer
typedef float f32;    // for decimals
typedef bool b32;     // for boolean

// ===== Utility Functions =====

// Check even number
static inline b32 isEven(s32 n)
{
    return (n % 2 == 0);
}

// Factorial
static inline uint64_t factorial(uint32_t n)
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

// made this for fun
typedef struct
{
    double x;
    double y;
} Vec2;

// maybe i'll use this someday
typedef struct
{
    double x, y, z;
} Vec3;
// making c function like python

#define and &&
#define or ||
#define not !
#define is ==
#define isnt !=

#endif