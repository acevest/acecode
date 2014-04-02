/*
 *--------------------------------------------------------------------------
 *   File Name:	tables.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Oct  6 19:19:37 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<asm/msr.h>
#include<beta/const.h>
#include<beta/system.h>
#include<beta/proc.h>
struct desc {
	unsigned short	limit_l;
	unsigned short	base_l;
	unsigned char	base_m;
    // s == 1 type(EXE, ED/C[扩展方向(0:向上, 1:向下)/代码段属性(0:不相容, 1:相容)], W/R, A[访问])
    // code seg: (EXE, ED, W, A)
    // data seg: (EXE, C, R, A)
    // s == 0 type
    // 0000     Reserved                1000    Reserved
    // 0001     有效的16位TSS           1001    有效的32位TSS
    // 0010     LDT                     1010    Reserved
    // 0011     正在执行的16位TSS       1011    正在执行的32位TSS
    // 0100     16位调用门              1100    32位调用门
    // 0101     任务门(16或32位)        1101    Reserved
    // 0110     16位中断门              1110    32位中断门
    // 0111     16位陷阱门              1111    32位陷阱门
	unsigned char	type	: 4;
	unsigned char	s	: 1;
	unsigned char	dpl	: 2;
	unsigned char	p	: 1;
	unsigned char	limit_h	: 4;
	unsigned char	avl	: 1;
	unsigned char	zero	: 1;
	unsigned char	db	: 1;
	unsigned char	g	: 1;
	unsigned char	base_h;
} __attribute__ ((packed));

struct gate {
	unsigned short	eaddr_l;
	unsigned short	selector;
	unsigned char	param	: 5;
	unsigned char	zero	: 3;
	unsigned char	type	: 4;
	unsigned char	s	: 1;
	unsigned char	dpl	: 2;
	unsigned char	p	: 1;
	unsigned short	eaddr_h;
} __attribute__ ((packed));

struct tss {
	unsigned short	backlink, _backlink;
	unsigned long	esp0;
	unsigned long	ss0, _ss0;
	unsigned long	esp1;
	unsigned long	ss1, _ss1;
	unsigned long	esp2;
	unsigned long	ss2, _ss2;
	unsigned long	cr3;
	unsigned long	eip;
	unsigned long	eflags;
	unsigned long	eax;
	unsigned long	ecx;
	unsigned long	edx;
	unsigned long	ebx;
	unsigned long	esp;
	unsigned long	ebp;
	unsigned long	esi;
	unsigned long	edi;
	unsigned short	es, _es;
	unsigned short	cs, _cs;
	unsigned short	ss, _ss;
	unsigned short	ds, _ds;
	unsigned short	fs, _fs;
	unsigned short	gs, _gs;
	unsigned short	ldt, _ldt;
	unsigned short	t	: 1;
	unsigned short	_t	: 15;
	unsigned short	iomap_base;
} __attribute__ ((packed));

#define	ALIGN_AT_PAGE_ROUND	__attribute__ ((__aligned__(PAGE_SIZE)))
struct desc	gdt[NGDT] 		ALIGN_AT_PAGE_ROUND;
struct desc	idt[NIDT] 		ALIGN_AT_PAGE_ROUND;
struct tss	tss			ALIGN_AT_PAGE_ROUND;
char intr_stack[INTR_STACK_SIZE]	ALIGN_AT_PAGE_ROUND;
char ring3_stack[RING3_STACK_SIZE]	ALIGN_AT_PAGE_ROUND;
void sysenter_entry();

void init_desc(struct desc *d){
	memset(d, 0, sizeof(struct desc));
}

struct desc create_gate(unsigned long handler, int type, int dpl) {

	struct desc d;
	struct gate *g = (struct gate *) &d;

	init_desc(&d);
	g->eaddr_l	= 0xFFFF & (handler);
	g->eaddr_h	= 0xFFFF & (handler >> 16);
	g->selector	= SELECTOR_KRNL_CS;
	g->type		= type;
	g->p		= 1;
	g->dpl		= dpl;

	return d;
}

struct desc create_tss_desc(unsigned long base) {

	struct desc d;

	init_desc(&d);

	d.limit_l	= 0xFFFF & (sizeof(struct tss));
	d.limit_h	= 0x000F & (sizeof(struct tss) >> 16);

	d.base_l	= 0xFFFF & (base);
	d.base_m	= 0x00FF & (base >> 16);
	d.base_h	= 0x00FF & (base >> 24);

	d.p		= 1;
	d.dpl		= PRI_USER;
	d.s		= 0;
	d.type		= TSS_DESC;

	return d;
}

struct table_register {
	unsigned short	limit;
	void		*base;
} __attribute__ ((packed));

struct table_register gdtr;
struct table_register idtr;

void switch_gdt() {

	asm("sgdt gdtr");
	memcpy(gdt, (void*)gdtr.base, gdtr.limit);
	gdtr.limit	= NGDT*sizeof(struct desc);
	gdtr.base	= gdt;
	asm("lgdt gdtr");


	gdt[INX_UCS] = gdt[INX_KCS];
	gdt[INX_UDS] = gdt[INX_KDS];
	gdt[INX_UCS].dpl = PRI_USER;
	gdt[INX_UDS].dpl = PRI_USER;
}

#define	set_gate(vect, type, DPL, handler)				\
do{									\
	extern	void	handler ();					\
	idt[vect] = create_gate((unsigned long )handler, type, DPL);	\
}while(0)

void no_irq_handler() {
	kprintf("%s\n", __FUNCTION__);
}

void init_idt() {

	int i;

	set_gate(0x00, TRAP_GATE, PRI_KRNL, divide_error);
	set_gate(0x01, TRAP_GATE, PRI_KRNL, debug);
	set_gate(0x02, TRAP_GATE, PRI_KRNL, nmi);
	set_gate(0x03, TRAP_GATE, PRI_USER, break_point);
	set_gate(0x04, TRAP_GATE, PRI_USER, over_flow);
	set_gate(0x05, TRAP_GATE, PRI_USER, bounds_check);
	set_gate(0x06, TRAP_GATE, PRI_KRNL, invalid_opcode);
	set_gate(0x07, TRAP_GATE, PRI_KRNL, device_not_available);
	set_gate(0x08, TRAP_GATE, PRI_KRNL, double_fault);
	set_gate(0x09, TRAP_GATE, PRI_KRNL, coproc_seg_over_run);
	set_gate(0x0A, TRAP_GATE, PRI_KRNL, invalid_tss);
	set_gate(0x0B, TRAP_GATE, PRI_KRNL, seg_not_present);
	set_gate(0x0C, TRAP_GATE, PRI_KRNL, stack_fault);
	set_gate(0x0D, TRAP_GATE, PRI_KRNL, general_protection);
	set_gate(0x0E, TRAP_GATE, PRI_KRNL, page_fault);
	set_gate(0x10, TRAP_GATE, PRI_KRNL, coproc_error);

	for(i=0x20; i<NIDT; i++)
		set_gate(i, INTR_GATE, PRI_KRNL, no_irq_handler);

	set_gate(0x20, INTR_GATE, PRI_KRNL, irq_0x00_handler);
	set_gate(0x21, INTR_GATE, PRI_KRNL, irq_0x01_handler);	
	set_gate(0x22, INTR_GATE, PRI_KRNL, irq_0x02_handler);	
	set_gate(0x23, INTR_GATE, PRI_KRNL, irq_0x03_handler);	
	set_gate(0x24, INTR_GATE, PRI_KRNL, irq_0x04_handler);	
	set_gate(0x25, INTR_GATE, PRI_KRNL, irq_0x05_handler);	
	set_gate(0x26, INTR_GATE, PRI_KRNL, irq_0x06_handler);	
	set_gate(0x27, INTR_GATE, PRI_KRNL, irq_0x07_handler);	
	set_gate(0x28, INTR_GATE, PRI_KRNL, irq_0x08_handler);	
	set_gate(0x29, INTR_GATE, PRI_KRNL, irq_0x09_handler);	
	set_gate(0x2A, INTR_GATE, PRI_KRNL, irq_0x0A_handler);	
	set_gate(0x2B, INTR_GATE, PRI_KRNL, irq_0x0B_handler);	
	set_gate(0x2C, INTR_GATE, PRI_KRNL, irq_0x0C_handler);	
	set_gate(0x2D, INTR_GATE, PRI_KRNL, irq_0x0D_handler);	
	set_gate(0x2E, INTR_GATE, PRI_KRNL, irq_0x0E_handler);	
	set_gate(0x2F, INTR_GATE, PRI_KRNL, irq_0x0F_handler);	

	idtr.limit	= NIDT*sizeof(struct desc);
	idtr.base	= idt;

	asm("lidt idtr");
}

void load_tss() {

	memset(&tss, 0, sizeof(tss));
	tss.ss0		= SELECTOR_KRNL_SS;
    tss.esp0    = (unsigned long) intr_stack;
    tss.esp0    +=INTR_STACK_SIZE;

	gdt[INX_TSS]	= create_tss_desc((unsigned long)&tss);

	asm("ltr %%ax": :"a"(INX_TSS*8|PRI_USER));
}

void setup_tables() {

	switch_gdt();

	init_idt();

	load_tss();

	kprintf("GDTR: Base: 0x%08x Limit: %d\n", gdtr.base, gdtr.limit);
	kprintf("IDTR: Base: 0x%08x Limit: %d\n", idtr.base, idtr.limit);

	kprintf("Interrupt Stack Base: 0x%08x Size:%d\n",
            intr_stack,
            sizeof(intr_stack));
}

void init_sysenter() {

	wrmsr(MSR_SYSENTER_CS,	SELECTOR_KRNL_CS,	0);
	wrmsr(MSR_SYSENTER_EIP,	sysenter_entry,		0);
	wrmsr(MSR_SYSENTER_ESP,	&current,			0);

}


void switch_to_user_mode(){
	void ring3();
	asm("andl	$0xFFFF, %%eax;"	\
		"andl	$0xFFFF, %%edx;"	\
		"movw	%%ax, %%ds;"		\
		"movw	%%ax, %%es;"		\
		"movw	%%ax, %%fs;"		\
		"movw	%%ax, %%gs;"		\
		"pushl	%%eax;"			\
		"pushl	%%ebx;"			\
		"pushl	$0x282;"		\
		"pushl	%%edx;"			\
		"pushl	%%ecx;"			\
		"iret;"				\
		:				\
		:"a"(SELECTOR_USER_DS | PRI_USER),
		 "b"(ring3_stack + RING3_STACK_SIZE),
		 //"c"(ring3),
		 "c"(proc[NR_PROC_INIT].eip),
		 "d"(SELECTOR_USER_CS | PRI_USER));
}

void ring3(){
	int beta_sysenter();
	int ret;
    int beta_notify();
	while(1){
		asm(""::"a"(1),"b"(2),"c"(3),"d"(4),"D"(5));
		ret = beta_sysenter();
		asm(""::"a"(ret));
		//asm("xchg %bx,%bx;");
        int i = 100000;
        while(i--);
        beta_notify();
	}
}
