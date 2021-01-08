#include <string.h>
#include <types.h>

void *memcpy(void *dest, const void *src, size_t n) {
    const u8 *src_ptr = src;
    u8 *dest_ptr = dest;
    while (n--) {
        *dest_ptr++ = *src_ptr++;
    }
    return dest;
}

void *memset(void *str, int c, size_t n) {
    u8 *str_ptr = str;
    while (n--) {
        *str_ptr++ = c;
    }
    return str;
}

size_t strlen(const char *str) {
    const char *c = str;
    size_t len = 0;
    for (;*c++;len++);
    return len; 
}