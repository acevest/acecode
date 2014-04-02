/*
 *--------------------------------------------------------------------------
 *   File Name:	exception.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Oct  6 20:47:57 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#define	die() do{\
	kprintf("Unsupport Now...[%s]\n", __FUNCTION__);	\
	while(1);						\
}while(0);

void do_divide_error(void *x)
{
	die();
}
void do_debug(void *x)
{
	die();
}
void do_nmi(void *x)
{
	die();
}
void do_break_point(void *x)
{
	die();
}
void do_over_flow(void *x)
{
	die();
}
void do_bounds_check(void *x)
{
	die();
}
void do_invalid_opcode(void *x)
{
	die();
}
void do_device_not_available(void *x)
{
	die();
}
void do_double_fault(void *x)
{
	die();
}
void do_coproc_seg_over_run(void *x)
{
	die();
}
void do_invalid_tss(void *x)
{
	die();
}
void do_seg_not_present(void *x)
{
	die();
}
void do_stack_fault(void *x)
{
	die();
}
void do_general_protection(void *x)
{
	die();
}
void do_page_fault(void *x)
{
}
void do_coproc_error(void *x)
{
	die();
}
