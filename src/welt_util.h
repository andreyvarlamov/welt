#ifndef WELT_UTIL_H
#define WELT_UTIL_H

void __debugbreak(); // usually in <intrin.h>

#define Breakpoint __debugbreak()
#define Noop { volatile int x = 0; }

#define ASSERT_STYLE 1

#if ASSERT_STYLE == 1
    #define Assert(expression) if (!(expression)) { printf("Assertion failed: %s", #expression); *((volatile int *) 0) = 0; }
#elif ASSERT_STYLE == 2
    #define Assert(expression) if (!(expression)) { __debugbreak(); }
#else
    #define Assert(expression)
#endif

#define global_var static
#define local_persist static
#define internal_func static

#define Kilobytes(Value) ((Value)*1024)
#define Megabytes(Value) (Kilobytes(Value)*1024)
#define Gigabytes(Value) (Megabytes(Value)*1024)
#define Terabytes(Value) (Gigabytes(Value)*1024)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define Max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define Min(X, Y) (((X) < (Y)) ? (X) : (Y))

#endif