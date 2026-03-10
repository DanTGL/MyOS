#include <string.h>

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size)
{

    unsigned char *dst       = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;

#ifdef __x86_64__
    asm volatile("cld; rep movsb"
                 : "=D"(dst), "=S"(src), "=c"(size)
                 : "0"(dst), "1"(src), "2"(size)
                 : "memory");
#else
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];

#endif /* ifdef __x86_64__ */

    return dstptr;
}
