#include <string.h>

void *__arch_memcpy(void *restrict dst, const void *restrict src, size_t count)
{
    asm volatile("cld; rep movsb"
                 : "=D"(dst), "=S"(src), "=c"(count)
                 : "0"(dst), "1"(src), "2"(count)
                 : "memory");

    return dst;
}
