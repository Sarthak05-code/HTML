#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ===== Basic Types =====
typedef uint8_t u8;   // unsigned 8 bit integer
typedef uint16_t u16; // unsigned 16 bit integer
typedef uint32_t u32; // unsigned 32 bit integer
typedef uint64_t u64; // unsigned 64 bit integer

typedef int8_t s8;   // signed 8 bit integer
typedef int16_t s16; // signed 16 bit integer
typedef int32_t s32; // signed 32 bit integer
typedef int64_t s64; // signed 64 bit integer

typedef float f32;  // float for 32 bit
typedef double f64; // 64 bit floating point 

typedef bool b8; // boolean and for historical convention

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