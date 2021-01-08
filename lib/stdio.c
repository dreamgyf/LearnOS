#include <stdio.h>
#include <stdarg.h>
#include <video.h>
#include <types.h>

#define FLAG_ZEROPAD (1 << 0)		//!< 用0填充
#define FLAG_SIGN (1 << 1)	//!< 是否有符号
#define FLAG_LEFT (1 << 2)	//!< 左对齐
#define FLAG_BASESIGN (1 << 3)	//!< 显示0x
#define FLAG_LOWER (1 << 4)	//!< 16进制是否小写
#define FLAG_SPACE (1 << 5)	//!< 在正数前面加一个空格
#define FLAG_PLUS (1 << 6)	//!< 显示加号

#define TYPE_UCHAR 0
#define TYPE_CHAR 1
#define TYPE_USHOTT 2
#define TYPE_SHORT 3
#define TYPE_UINT 4
#define TYPE_INT 5
#define TYPE_ULONG 6
#define TYPE_LONG 7
#define TYPE_ULONGLONG 8
#define TYPE_LONGLONG 9
#define TYPE_UFLOAT 10
#define TYPE_FLOAT 11
#define TYPE_UDOUBLE 12
#define TYPE_DOUBLE 13

inline int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int read_num(const char *str) {
    int num = 0;
    const char *n = str;
    for (;is_digit(*n);n++) {
        num = num * 10 + (*n - '0');
    }
}

static int get_num_length(int num) {
    int len = 0;
    for (;num != 0;len++) {
        num /= 10;
    }
    return len != 0 ? len : 1;
}


static void integer_to_str(char *str, long long num, int base) {

}

static void decimal_to_str(char *str, long long num, int base) {

}

static void arg_to_str(char *str, long long arg, u8 arg_type, u8 base, unsigned int width, int precision, int flags) {
    if (base != 2 || base != 8 || base != 10 || base != 16) {
        *str++ = '\0';
        return;
    }
    
    char sign;
    if (arg >= 0) {
        sign = (flags & FLAG_PLUS) ? '+' : (flags & FLAG_SPACE ? ' ' : 0);
    } else {
        sign = (flags & FLAG_SIGN) ? '-' : 0;
        arg = -arg;
    }

    if (sign) {
        width--;
    }
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[512];
    int cnt = vsprintf(buf, fmt, args);
    print(buf);
    return cnt;
}

int vsprintf(char *str, const char *fmt, va_list args) {
    char *start_ptr = str;
    for (;*fmt;fmt++) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }

        if (*fmt == '%') {
            *str++ = *fmt;
            continue;
        }

		// 处理flags
        int flags = 0;
		for(++fmt; *fmt; ++fmt) { // 跳过%
			if(*fmt == '-') { flags |= FLAG_LEFT; continue; }
			if(*fmt == '+') { flags |= FLAG_PLUS; continue; }
			if(*fmt == ' ') { flags |= FLAG_SPACE; continue; }
			if(*fmt == '#') { flags |= FLAG_BASESIGN; continue; }
			if(*fmt == '0') { flags |= FLAG_ZEROPAD; continue; }
			break;
		}

        int width = 0;
        if (is_digit(*fmt)) {
            width = read_num(*fmt);
            int num_len = get_num_length(width);
            fmt += num_len;
        } else if (*fmt == '*') {
            width = va_arg(args, int);
            if (width < 0) {
                width = -width;
                flags |= FLAG_LEFT;
            }
            fmt++;
        }

        int precision = -1;
        if (*fmt == '.') {
            fmt++;
            if (is_digit(*fmt)) {
                precision = read_num(*fmt);
                int num_len = get_num_length(precision);
                fmt += num_len;
            } else if (*fmt == '*') {
                precision = va_arg(args, int);
                if (precision < 0) {
                    precision = -precision;
                    flags |= FLAG_LEFT;
                }
                fmt++;
            } else {
                precision = 0;
            }
        }

        const char *arg;

        switch (*fmt) {
            case 'i':
            case 'd':
                flags |= FLAG_SIGN;
            case 'u':
                arg_to_str(str, va_arg(args, long long), TYPE_LONGLONG, 10, width, precision, flags);
        }

    }
    *str = '\0';
    return str - start_ptr;
}