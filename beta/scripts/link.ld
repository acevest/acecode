/*
 *--------------------------------------------------------------------------
 *   File Name:	link.ld
 * 
 * Description: Link All Object Files to KERNEL ...
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.1
 * Create Date: Mon Mar  2 12:21:03 2009
 * Last Update: Mon Mar  2 12:21:03 2009
 * 
 *--------------------------------------------------------------------------
 */

OUTPUT_FORMAT("elf32-i386")
ENTRY(BETA_ENTRY)
PHY = 0x100000;
SECTIONS
{
	. = PHY;
    kernel_start = .;
	.text . : AT(PHY) ALIGN(0x1000)
	{
		*(.init);
		. = ALIGN(0x1000);
		code = .;
		*(.text)
	}
	etext = .;

	.data : AT(PHY + (data - code)) ALIGN(0x1000) 
	{
		data = .;
		*(.data)
		*(.rodata)
	}
	edata = .;

	.bss : AT(PHY + (bss - code))  ALIGN(0x1000)
	{
		bss = .;
		*(.bss);
	}
	ebss = .;
	end = .;

	. = ALIGN(0x1000);
	kernel_end = .;
}
