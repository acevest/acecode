/*
 *--------------------------------------------------------------------------
 *   File Name:	irq.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 16:40:42 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<sys/types.h>
#include<asm/ptrace.h>
#include<beta/irq.h>

extern	struct irq_desc i8259_irq_desc;
struct irq_desc irq_desc[NR_IRQS];

int no_irq_chip_enable(unsigned int irq){return 0;}
int no_irq_chip_disable(unsigned int irq){return 0;}
int no_irq_chip_ack(unsigned int irq){return 0;}
int no_irq_chip_end(unsigned int irq){return 0;}

struct irq_chip no_irq_chip = {
	.name		= "none",
	.enable		= no_irq_chip_enable,
	.disable	= no_irq_chip_disable,
	.ack		= no_irq_chip_ack,
	.end		= no_irq_chip_end
};

struct irq_desc no_irq_desc = {
	.chip	= &no_irq_chip,
	.action	= NULL,
};

void irq_handler(pt_regs r){

	unsigned int irq = r.irq;

	struct irq_desc		*d = irq_desc + irq;
	struct irq_action	*a = d->action;

	d->chip->ack(irq);

	while(a){
		a->handler(irq, &r, NULL);
		a = a->next;
	}

	d->chip->end(irq);
}


int clock_handler(unsigned int irq, pt_regs *r, void *dev_id);
struct irq_action clock_irq_action = {
	.handler	= clock_handler,
	.dev_name	= "timer",
	.dev_id		= NULL,
	.next		= NULL,
};
#include <asm/io.h>
int kbd_handler(unsigned int irq, pt_regs *r, void *dev_id) {
    char c = inb(0x60);
	unsigned char *p = (unsigned char *)0xB8004;
    if(*p <'A' || *p>='Z')
        *p = 'A';
	else
        *p = ++*p;
}
struct irq_action kbd_irq_action = {
    .handler    = kbd_handler,
    .dev_name   = "keyboard",
    .dev_id     = NULL,
    .next       = NULL,
};

void setup_irqs()
{
	int i;

	for(i=0; i<16; i++){
		irq_desc[i] = i8259_irq_desc;
	}
	for(i=16; i<NR_IRQS; i++){
		irq_desc[i] = no_irq_desc;
	}

	irq_desc[0].action = &clock_irq_action;
	irq_desc[1].action = &kbd_irq_action;
}
