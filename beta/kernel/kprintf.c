/*
 *--------------------------------------------------------------------------
 *   File Name:	kprintf.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Oct  5 11:03:33 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<stdarg.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>

int isdigit(int c)
{
	return (c>='0' && c<='9');
}

int cton(int c)
{
	return (c-'0');
}


#define	ROWSZ	25
#define	COLSZ	80
#define	VGABASE	(0xB8000)

void kputc(int c)
{
	int	xpos, ypos;
	char	ch = 0;
	static short *p = (short *)VGABASE;

	xpos = (p-(short*)VGABASE) % COLSZ;
	ypos = (p-(short*)VGABASE) / COLSZ;

	switch(c){
	case '\n':
		p = (short *)VGABASE + (ypos+1)*COLSZ;
		break;
	case '\t':
		p = (short *)VGABASE + ((xpos+7)/8)*8 + ypos*COLSZ;
		break;
	case '\b':
	case '\r':
		break;
	default:
		ch = c;
	}

	if(ypos == ROWSZ){
		memcpy((void *)VGABASE, (void *)(VGABASE+COLSZ*2),
			COLSZ*2*(ROWSZ-1));
		memset((void *)(VGABASE+COLSZ*(ROWSZ-1)*2), 0, COLSZ*2);
		p -= COLSZ;
	}

	if(ch){
		*p++ = (short)(0x0200 | ch);
	}
}

int kprintf(const char *fmt, ...)
{
	int c;
	int d;
	unsigned long u;
	int base;
	char x2c[]="0123456789ABCDEF";
	int ascii[64];
	int negative, zero;
	char *s;
	int ch;
	int n;
	va_list argp;

	va_start(argp, fmt);

	while((c=*fmt++) != 0){
		if(c != '%'){
			kputc(c);
			continue;
		}

		c = *fmt++;
		if(c == '0'){
			zero = 0;
			while(isdigit(c = *fmt++)){
				zero *= 10;
				zero += cton(c);
			}
		}

		negative = 0;
		s = NULL;

		switch(c){
		case 'd':
			d = va_arg(argp, int);
			u = d;
			base = 10;
			if(d < 0){
				negative = 1;
				u = -d;
			}
			break;
		case 'u':
			u = va_arg(argp, unsigned long);
			base = 10;
			break;
		case 'x':
			u = va_arg(argp, unsigned long);
			base = 0x10;
			break;
		case 'c':
			ch = va_arg(argp, int);
			ascii[0] = (char)ch;
			ascii[1] = 0;
			s = (char *)ascii;
			break;
		case 's':
			s = va_arg(argp, char *);
			if(s == NULL) s = "(NULL)";
			break;
		case '%':
			s = "%";
			break;
		default:
			assert(0);
		}

		if(s == NULL){
			s = (char *)(ascii + sizeof(ascii) - 1);
			*s = 0;
			do{
				*--s = x2c[u % base];
			}while((u /= base) > 0);

			if(zero != 0){
				n = zero - strlen(s);
				while(n--) *--s = '0';
				zero = 0;
			}
		}

		if(negative) kputc('-');
		while(*s != 0){
			kputc(*s++);
		}
	}
	va_end(argp);
}
