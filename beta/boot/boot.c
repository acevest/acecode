/*
 *--------------------------------------------------------------------------
 *   File Name:	boot.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 20:30:10 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<multiboot.h>
#include<assert.h>
#include<sys/video.h>
#include<beta/proc.h>
#include<asm/io.h>
int kprintf(const char *fmt, ...);
void analyze_elf(const char *data, vaddr_t *entry);
extern char kernel_start;
extern char kernel_end;
extern void BETA_ENTRY();
void clear_screen() {
    int i, j;
    for(i=0; i<25; i++) {
        for(j=0; j<80; j++) {

        }
    }

    outb(VGA_CRTC_BASE + VGA_INDEX, VGA_CURSOR_H);
    outb(VGA_CRTC_BASE + VGA_DATA,  0);
    outb(VGA_CRTC_BASE + VGA_INDEX, VGA_CURSOR_L);
    outb(VGA_CRTC_BASE + VGA_DATA,  4);
}
void multi_boot(unsigned long magic, multiboot_info_t *mbi)
{
    clear_screen();
    kprintf("                                                   \n");
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	kprintf("Boot Loader: %s\n", mbi->boot_loader_name);
    kprintf("Kernel: [0x%08x - 0x%08x] Entry: 0x%08x\n",
            &kernel_start,
            &kernel_end,
            BETA_ENTRY);

    int i;
    module_t *module = (module_t *) mbi->mods_addr;
    for(i=0; i<mbi->mods_count; i++) {
        vaddr_t *entry = (vaddr_t) &(proc[NR_PROC_START+i].eip);

        kprintf("Module: [0x%08x - 0x%08x]", 
                module->mod_start,
                module->mod_end);

        analyze_elf((const char *) module->mod_start, entry);

        //kprintf("eip:%08x\n", proc[NR_PROC_START+i].eip);
        module++;
    }
}
