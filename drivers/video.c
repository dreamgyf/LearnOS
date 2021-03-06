#include <video.h>
#include <io.h>
#include <string.h>

u8 * const VRAM = (u8*)VRAM_ADDRESS;

static inline int get_vt_offset(int row, int col) {
	return (row * MAX_COL + col) * 2;
}

//获取当前光标的偏移位置。
static int get_vt_cursor(void) {
// REG_SCREEN_CTRL 写入14，控制访问偏移量的高字节
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
// REG_SCREEN_CTRL 写入15，控制访问偏移量的低字节
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset |= port_byte_in(REG_SCREEN_DATA);
	return offset * 2;
}

//设置光标位置。
static void set_vt_cursor(int offset) {
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (u8)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (u8)(offset & 0xff));
}

static inline int is_out_of_range(int offset) {
	return offset >= MAX_COL * MAX_ROW * 2;
}

static void vt_scroll_up_one_line() {
	memcpy(VRAM + get_vt_offset(0, 0), VRAM + get_vt_offset(1, 0), MAX_COL * (MAX_ROW - 1) * 2);
	u8 *last_line = VRAM + get_vt_offset(MAX_ROW - 1, 0);
	for(int i = 0; i < MAX_COL; ++i) {
		last_line[i * 2] = 0;
	}
}

static int handle_vt_scroll(int offset) {
	if(!is_out_of_range(offset)) {
        return offset;
    }

	vt_scroll_up_one_line();
	
	offset -= 2 * MAX_COL;
	return offset;
}

static void nextCoords(int *row, int *col) {
	if (*col >= 0 && *col < MAX_COL - 1) {
		(*col)++;
	} else if (*col >= 0 && *col == MAX_COL - 1) {
		(*row)++;
		*col = 0;
	}

	if (is_out_of_range(get_vt_offset(*row, *col))) {
		(*row)--;
	}
}

void print(const char *str) {
    print_at(str, -1, -1);
}

void print_at(const char *str, int row, int col) {
	int r = row;
	int c = col;
    for (;*str;str++) {
        print_char(*str, r, c, 0);
		nextCoords(&r, &c);
    }
}

void print_char(char c, int row, int col, char attr) {
    if (!attr) {
        attr = WHITE_ON_BLACK;
    }

    int offset;
    if (row >= 0 && row < MAX_ROW && col >= 0 && col < MAX_COL) {
        offset = get_vt_offset(row, col);
        set_vt_cursor(offset);
    } else {
        offset = get_vt_cursor();
    }

    switch(c) {
		case '\n':
			offset = get_vt_offset(offset / MAX_COL / 2 + 1, 0);
			break;
		case '\t':
			offset += TABSIZE - offset % TABSIZE;
			break;
		default:
			VRAM[offset] = c;
			VRAM[offset + 1] = attr;
			offset += 2;
			break;
	}

    offset = handle_vt_scroll(offset);
    set_vt_cursor(offset);
}