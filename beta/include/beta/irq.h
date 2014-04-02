/*
 *--------------------------------------------------------------------------
 *   File Name:	irq.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 20:23:55 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_IRQ_H
#define	_IRQ_H

#include<asm/ptrace.h>

#define	NR_IRQS	(224)

struct irq_chip {
	const char *name;
	int (*enable)(unsigned int irq);
	int (*disable)(unsigned int irq);
	int (*ack)(unsigned int irq);
	int (*end)(unsigned int irq);
};

struct irq_action {
	int (*handler)(unsigned int irq, pt_regs *r, void *dev_id);
	const char		*dev_name;
	void			*dev_id;
	struct irq_action	*next;
};

struct irq_desc {
	struct irq_chip		*chip;
	struct irq_action	*action;
};

extern struct irq_desc irq_desc[NR_IRQS];


#define	IRQ_TIMER	0x00
#define	IRQ_KBD		0x01
#define	IRQ_HD		0x0E

#endif //_IRQ_H
