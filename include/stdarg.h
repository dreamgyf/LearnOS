#ifndef _STDARG_H
#define _STDARG_H

typedef char* va_list;

#define va_start(ap, pN)	\
	((ap) = ((va_list) (&pN) + __va_argsiz(pN)))

#define va_end(ap)	((void)0)

#define va_arg(ap, t)					\
    (((ap) = (ap) + __va_argsiz(t)),		\
     *((t*) (void*) ((ap) - __va_argsiz(t))))

#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#endif