#ifndef _IO_H
#define _IO_H

#include <types.h>

// in 指令，从IO端口读取数据
u8 port_byte_in(u16 port);
u16 port_word_in(u16 port);

// out 指令，往IO端口输出数据
void port_byte_out(u16 port, u8 data);
void port_word_out(u16 port, u16 data);

#endif