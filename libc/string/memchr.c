#include <string.h>

void *memchr(const void *ptr, int ch, size_t count)
{
    const unsigned char *str = ptr;

    for (size_t i = 0; i < count; ++i) {
        if (str[i] == ch) {
            return (void *)&str[i];
        }
    }

    return NULL;
}
