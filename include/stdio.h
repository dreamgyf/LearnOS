#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

int printf(const char *fmt, ...);
int vsprintf(char * str, const char * fmt, va_list arg);

#endif