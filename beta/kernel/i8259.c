/*
 *--------------------------------------------------------------------------
 *   File Name:	i8259.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 17:21:27 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<asm/io.h>
#include<beta/irq.h>

#define	PIC_MASTER_CMD	0x20
#define	PIC_MASTER_IMR	0x21		/* Interrupt Mask Register */
#define	PIC_MASTER_IRR	PIC_MASTER_CMD	/* Interrupt Request Register */
#define	PIC_MASTER_ISR	PIC_MASTER_CMD	/* In Service Register */

#define	PIC_SLAVER_CMD	0xA0
#define	PIC_SLAVER_IMR	0xA1
#define	PIC_SLAVER_IRR	PIC_SLAVER_CMD
#define	PIC_SLAVER_ISR	PIC_SLAVER_CMD

#define	PIC_CASCADE_IR	0x02 /* The IR2 on Master Connect to Slave */


static inline void i8259_mask_all(){
    outb(PIC_MASTER_IMR,    0xFF);
    outb(PIC_SLAVER_IMR,    0xFF);
}

void i8259_remap(){

	i8259_mask_all();

	/* ICW1 */
	outb(PIC_MASTER_CMD,    0x11);
	outb(PIC_SLAVER_CMD,    0x11);

	/* ICW2 */
	outb(PIC_MASTER_IMR,    0x20);
	outb(PIC_SLAVER_IMR,    0x28);

	/* ICW3 */
    outb(PIC_MASTER_IMR,    1UL<<PIC_CASCADE_IR);
    outb(PIC_SLAVER_IMR,    PIC_CASCADE_IR);

	/* ICW4 */
	outb(PIC_MASTER_IMR,    0x01);
	outb(PIC_SLAVER_IMR,    0x01);

	i8259_mask_all();

	i8259_enable(IRQ_TIMER);
	i8259_enable(IRQ_KBD);
}

int	i8259_enable(unsigned int irq){

	unsigned char mask = ~(1<<irq);

	if(irq & 8){	/* Slave */
		mask &= inb(PIC_SLAVER_IMR);
		outb(PIC_SLAVER_IMR,    mask);
	}else{		/* Master */
		mask &= inb(PIC_MASTER_IMR);
		outb(PIC_MASTER_IMR,    mask);
	}

	return 0;
}

int i8259_disable(unsigned int irq){

	unsigned char mask = 1<<irq;

	if(irq & 8){	/* Slave */
		mask |= inb(PIC_SLAVER_IMR);
		outb(PIC_SLAVER_IMR,    mask);
	}else{		/* Master */
		mask |= inb(PIC_MASTER_IMR);
		outb(PIC_MASTER_IMR,    mask);
	}

	return 0;
}

int i8259_mask_and_ack(unsigned int irq){

	unsigned char mask = 1<<irq;

	if(irq & 8){	/* Slave */
		
		mask |= inb(PIC_SLAVER_IMR);
		outb(PIC_SLAVER_IMR,    mask);

        outb(PIC_SLAVER_CMD,    0x60 + (irq & 0x07));
        outb(PIC_SLAVER_CMD,    0x60 + (PIC_CASCADE_IR & 0x07));
		
	}else{		/* Master */
		mask |= inb(PIC_MASTER_IMR);
		outb(PIC_MASTER_IMR,    mask);

		outb(PIC_MASTER_CMD,    0x60 + irq);
	}

	return 0;
}


struct irq_chip i8259_irq_chip = {
	.name		= "XT-PIC",
	.enable		= i8259_enable,
	.disable	= i8259_disable,
	.ack		= i8259_mask_and_ack,
	.end		= i8259_enable,
};

struct irq_desc i8259_irq_desc = {
	.chip	= &i8259_irq_chip,
	.action	= NULL,
};
