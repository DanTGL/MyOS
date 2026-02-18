#include <string.h>

#ifdef ARCH_MEMCPY
void *__arch_memcpy(void *restrict, const void *restrict, size_t);
#endif /* ifdef ARCH_MEMCPY */

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size)
{
#ifdef ARCH_MEMCPY
    return __arch_memcpy(dstptr, srcptr, size);
#else
    unsigned char *dst = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;

#endif /* ifdef ARCH_MEMCPY */
}
