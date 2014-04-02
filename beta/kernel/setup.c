/*
 *--------------------------------------------------------------------------
 *   File Name:	setup.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 20:28:36 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#define sti() asm("sti;")

const char *version;

void setup_tables();
void i8259_remap();
void setup_irqs();
void setup_syscall();
void switch_to_user_mode();
void setup_proc();
int kprintf(const char *fmt, ...);


void kernel_entry()
{
	setup_tables();

	i8259_remap();

    setup_proc();

	setup_irqs();

	setup_syscall();


	kprintf("Welcome to use %s\n", version);

	sti();
	
	switch_to_user_mode();
}
