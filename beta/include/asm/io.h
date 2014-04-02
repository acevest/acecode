/*
 *--------------------------------------------------------------------------
 *   File Name:	io.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 18:38:08 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_IO_H
#define	_IO_H

#include<sys/types.h>

#define outb_p(port, value)({ 				\
	asm(	"outb %%al,%%dx;nop;nop;nop;nop" 	\
		: 					\
		:"a" (value),"d" (port)); 		\
})

#define inb_p(port)({ 					\
	u8_t _bt; 					\
	asm("inb	%%dx,%%al;nop;nop;nop;nop"	\
		:"=a" (_bt) 				\
		:"d" (port)); 				\
	_bt; 						\
})




#define outb(port, value)({ 				\
	asm(	"outb	%%al,%%dx" 			\
		: 					\
		:"a" (value),"d" (port)); 		\
})

#define outw(port, value)({ 				\
	asm(	"outw	%%ax,%%dx" 			\
		: 					\
		:"a" (value),"d" (port)); 		\
})

#define outl(port, value)({ 				\
	asm(	"outl	%%eax,%%dx" 			\
		: 					\
		:"a" (value),"d" (port)); 		\
})




#define inb(port)({ 					\
	u8_t _bt; 					\
	asm(	"inb	%%dx,%%al" 			\
		:"=a" (_bt) 				\
		:"d" (port)); 				\
	_bt; 						\
})

#define inw(port)({ 					\
	u16_t _bt; 					\
	asm(	"inw	%%dx,%%ax" 			\
		:"=a" (_bt) 				\
		:"d" (port)); 				\
	bt; 						\
})

#define inl(port)({ 					\
	u32_t _bt; 					\
	asm(	"inl	%%dx,%%eax" 			\
		:"=a" (_bt) 				\
		:"d" (port)); 				\
	_bt; 						\
})




#define	BUILDIO(bwl, type)				\
static inline void ins##bwl(int port, void *buf, unsigned long count)	\
{									\
	asm volatile(	"cld;rep;ins" #bwl				\
			: "+c"(count), "+D"(buf) : "d"(port));		\
}


BUILDIO(b, char)
BUILDIO(w, short)
BUILDIO(l, int)

#endif //_IO_H
