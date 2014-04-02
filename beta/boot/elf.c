/*
 * ------------------------------------------------------------------------
 *   File Name: elf.c
 *      Author: Zhao Yanbai
 *              Mon Apr  2 15:59:26 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<sys/types.h>
#include<elf.h>
int kprintf(const char *fmt, ...);

void analyze_elf(const char *data, vaddr_t *entry) {
    int i;
    void *vaddr, *paddr;
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) data;
    Elf32_Phdr *phdr = NULL;
    vaddr = paddr = NULL;

    *entry = (vaddr_t) ehdr->e_entry;
    kprintf(" Entry: 0x%08x\n", *entry); 
    for(i=0; i<ehdr->e_phnum; i++) {

        phdr = (Elf32_Phdr *) (data + ehdr->e_phoff + ehdr->e_phentsize*i);

        if(phdr->p_type != PT_LOAD) {
            //kprintf("Type:%x\n", phdr->p_type && 0xFFFF);
            continue;
        }

        kprintf("   -Vaddr: 0x%08x Paddr: 0x%08x\n",
                phdr->p_vaddr,
                phdr->p_paddr);

        memcpy(phdr->p_paddr, data + phdr->p_offset, phdr->p_memsz);
    }
}
