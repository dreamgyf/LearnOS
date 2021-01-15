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

typedef struct {
    int width;
    int int_width;
    int dec_width;
} decimal_struct;

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int read_num(const char *str) {
    int num = 0;
    const char *n = str;
    for (;is_digit(*n);n++) {
        num = num * 10 + (*n - '0');
    }
    return num;
}

static int get_num_length(int num) {
    int len = 0;
    for (;num != 0;len++) {
        num /= 10;
    }
    return len != 0 ? len : 1;
}


static int integer_to_str(char *str, unsigned long num, int base, BOOL is_lower) {
    char *digits = is_lower ? "0123456789abcdef" : "0123456789ABCDEF";
    char *c = str;

    if (num == 0) {
        *c++ = '0';
        *c = '\0';
        return 1;
    }

    char tmp[256];
    int count = 0;
    while (num) {
        tmp[count++] = digits[num % base];
        num /= base;
    }
    
    for (int i = count - 1; i >= 0; i--) {
        *c++ = tmp[i];
    }
    *c = '\0';
    return count;
}

static decimal_struct decimal_to_str(char *str, double num, int precision, int base, BOOL is_lower) {
    char *digits = is_lower ? "0123456789abcdef" : "0123456789ABCDEF";
    decimal_struct ds;

    ds.int_width = integer_to_str(str, num, base, is_lower);
    
    int int_part = (int)num;
    double dec_part = num - (double)int_part;
    if (dec_part == 0 || precision == 0) {
        ds.dec_width = 0;
        ds.width = ds.int_width;
        return ds;
    }

    int offset = ds.int_width;
    str[offset++] = '.';
    while (dec_part != 0 && precision--) {
        dec_part *= base;
        unsigned int tmp = dec_part;
        str[offset++] = digits[tmp];
        dec_part = dec_part - (int)dec_part;
    }
    str[offset] = '\0';

    ds.dec_width = offset - ds.int_width - 1;
    ds.width = ds.int_width + ds.dec_width + 1;
    return ds;
}

static char* arg_to_str(char *str, double arg, u8 arg_type, u8 base, unsigned int width, int precision, int flags) {
    if (base != 2 && base != 8 && base != 10 && base != 16) {
        *str++ = '\0';
        return str;
    }
                
    if(flags & FLAG_LEFT) flags &= ~FLAG_ZEROPAD;
    
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

    if(flags & FLAG_BASESIGN) {
		if(base == 8) {
            --width;
        } else if (base == 16) {
            width -= 2;
        }
	}

    char num[256];
    int num_count = 0;
    if (arg_type == TYPE_LONG) {
        num_count = integer_to_str(num, arg, base, flags & FLAG_LOWER);
    } else if (arg_type == TYPE_DOUBLE) {
        if (precision < 0)
            precision = 6;
            
        decimal_struct ds = decimal_to_str(num, arg, precision, base, flags & FLAG_LOWER);
        num_count = ds.width;

        if (precision >= 0) {
            int dot_index = ds.dec_width > 0 ? ds.int_width : -1;
            int last_index = -1 + ds.int_width + ds.dec_width + (ds.dec_width > 0 ? 1 : 0);

            if (precision > ds.dec_width) {
                ++last_index;
                if (dot_index == -1) {
                    num[last_index++] = '.';
                    ++num_count;
                }
                while (precision >= last_index - ds.int_width) {
                    num[last_index++] = '0';
                    ++num_count;
                }
                num[last_index] = '\0';
            } else if (precision < ds.dec_width) {
                while (precision <= last_index - ds.int_width - 1) {
                    --last_index;
                    --num_count;
                }

                if (num[last_index] == '.') {
                    --last_index;
                    --num_count;
                }

                num[++last_index] = '\0';
            }
        }
    }

    if (!(flags & (FLAG_ZEROPAD | FLAG_LEFT))) {
        for (;width > num_count; width--) {
            *str++ = ' ';
        }
    } 

    if (flags & FLAG_ZEROPAD) {
        for (;width > num_count; width--) {
            *str++ = '0';
        }
    }

    if (sign) {
        *str++ = sign;
    }

    if (flags & FLAG_BASESIGN) {
        if (base == 8) {
            *str++ = '0';
        } else if (base == 16) {
            *str++ = '0';
            *str++ = (flags & FLAG_LOWER) ? 'x' : 'X';
        }
    }

    for (int i = 0; i < num_count; i++) {
        *str++ = num[i];
    }

    if (flags & FLAG_LEFT) {
        for (;width > num_count; width--) {
            *str++ = ' ';
        }
    }

    return str;
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[512];
    int cnt = vsprintf(buf, fmt, args);
    va_end(args);
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
        
        if (*++fmt == '%') {
            *str++ = *fmt;
            continue;
        }

		// 处理flags
        int flags = 0;
		for(; *fmt; ++fmt) { // 跳过%
			if(*fmt == '-') { flags |= FLAG_LEFT; continue; }
			if(*fmt == '+') { flags |= FLAG_PLUS; continue; }
			if(*fmt == ' ') { flags |= FLAG_SPACE; continue; }
			if(*fmt == '#') { flags |= FLAG_BASESIGN; continue; }
			if(*fmt == '0') { flags |= FLAG_ZEROPAD; continue; }
			break;
		}

        int width = 0;
        if (is_digit(*fmt)) {
            width = read_num(fmt);
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
                precision = read_num(fmt);
                int num_len = get_num_length(precision);
                fmt += num_len;
            } else if (*fmt == '*') {
                precision = va_arg(args, int);
                fmt++;
            }
        }

        const char *arg;

        switch (*fmt) {
            case 'i':
            case 'd':
                flags |= FLAG_SIGN;
            case 'u':
                str = arg_to_str(str, va_arg(args, long), TYPE_LONG, 10, width, precision, flags);
                break;
            case 'f':
                flags |= FLAG_SIGN;
                str = arg_to_str(str, va_arg(args, double), TYPE_DOUBLE, 10, width, precision, flags);
                break;
        }

    }
    *str = '\0';
    return str - start_ptr;
}