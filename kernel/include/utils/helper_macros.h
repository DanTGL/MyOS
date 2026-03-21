#ifndef MYOS_UTILS_HELPER_MACROS_H
#define MYOS_UTILS_HELPER_MACROS_H

#define UNUSED(x) ((void)(x))

#define BIT      (1UL << (n))
#define BIT64(n) (1ULL << (n))

#define BIT_TYPED(n, type) (((type)1U) << (n))

#define BIT_SET(x, n)   ((x) | BIT_TYPED(n, typeof(x)))
#define BIT_CLEAR(x, n) ((x) & (~BIT_TYPED(n, typeof(x))))
#define BIT_TOGGLE(x, n) ((x) ^ (BIT_TYPED(n, typeof(x)))

#endif // !MYOS_UTILS_HELPER_MACROS_H
