#ifndef TYPES_DATA_TYPES
#define TYPES_DATA_TYPES
typedef unsigned int u32;
typedef int b32;
typedef float f32;





static inline b32 isEven(int n){
    return (n % 2 == 0);
}

static inline u32 factorial(u32 n){
    u32 result = 1;
    for(u32 i = 1 ; i <= n ; ++i){
        result *= i;
    }
    return result;
}

#endif