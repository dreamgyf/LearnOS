#ifndef _STRING_H
#define _STRING_H

#include <types.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *str, int c, size_t n);
size_t strlen(const char *str);

#endif