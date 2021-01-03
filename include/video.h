#ifndef _VIDEO_H
#define _VIDEO_H

//显存地址
#define VRAM_ADDRESS 0xb8000

//机器启动后，图像硬件初始为VGA文本模式（另一种模式为图像模式），能显示80x25个字符，用2个字节表示一个字符。
#define MAX_ROW 25
#define MAX_COL 80
#define WHITE_ON_BLACK 0x0f //!< 黑底白字

/** 屏幕设备的IO端口。
 * - REG_SCREEN_CTRL 写入14，控制访问偏移量的高字节
 * - REG_SCREEN_CTRL 写入15，控制访问偏移量的低字节
 * - 读或写REG_SCREEN_DATA来访问偏移量的高低字节。
*/
#define REG_SCREEN_CTRL 0x3d4 //屏幕控制端口
#define REG_SCREEN_DATA 0x3d5 //屏幕数据端口

#define TABSIZE 8 //TAB制表符的长度

void print(const char *str);
void print_at(const char* str, int row, int col);
void print_char(char c, int row, int col, char attr);

#endif