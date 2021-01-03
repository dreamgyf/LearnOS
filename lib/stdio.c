#include <stdio.h>
#include <stdarg.h>
#include <video.h>

#define FLAG_ZEROPAD (1 << 0)		//!< 用0填充
#define FLAG_SIGN (1 << 1)	//!< 是否有符号
#define FLAG_LEFT (1 << 2)	//!< 左对齐
#define FLAG_BASESIGN (1 << 3)	//!< 显示0x
#define FLAG_LOWER (1 << 4)	//!< 16进制是否小写
#define FLAG_SPACE (1 << 5)	//!< 在正数前面加一个空格
#define FLAG_PLUS (1 << 6)	//!< 显示加号

inline int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[512];
    int cnt = vsprintf(buf, fmt, args);
    print(buf);
    return cnt;
}

int vsprintf(char *str, const char *fmt, va_list arg) {
    char *start_ptr = str;
    for (;*fmt;fmt++) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }

        int flags = 0, width = 0, precision = -1;
		// 处理flags
		for(++fmt; *fmt; ++fmt) { // 跳过%
			if(*fmt == '-') { flags |= FLAG_LEFT; continue; }
			if(*fmt == '+') { flags |= FLAG_PLUS; continue; }
			if(*fmt == ' ') { flags |= FLAG_SPACE; continue; }
			if(*fmt == '#') { flags |= FLAG_BASESIGN; continue; }
			if(*fmt == '0') { flags |= FLAG_ZEROPAD; continue; }
			break;
		}
    }
    return str - start_ptr;
}