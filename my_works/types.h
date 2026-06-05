#ifndef TYPES_H
#define TYPES_H

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ===== Basic Types =====
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

typedef bool b8;

// ===== Utility Functions =====

static inline b8 isEven(s32 n)
{
    return (n % 2 == 0);
}

static inline u64 factorial(u32 n)
{
    u64 result = 1;

    for (u32 i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

static inline void arrayPrinter(const u32 *array, u32 n)
{
    for (u32 i = 0; i < n; i++)
    {
        printf("%u\t", array[i]);
    }
    printf("\n");
}

// ===== Math Constants =====
#define PI 3.14159265358979323846
#define TAU 6.28318530717958647692
#define E 2.71828182845904523536

#define DEG_TO_RAD (PI / 180.0)
#define RAD_TO_DEG (180.0 / PI)

// ===== Structs =====
typedef struct
{
    f64 x;
    f64 y;
} Vec2;

typedef struct
{
    f64 x, y, z;
} Vec3;

// ===== Fun Macros (unsafe but fun) =====
#define and &&
#define or ||
#define not !
#define is ==
#define isnt !=
#define is_lesser_equal <=
#define is_greater_equal >=
#define is_less <
#define is_greater >

#endif