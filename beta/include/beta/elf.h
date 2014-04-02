/*
 *--------------------------------------------------------------------------
 *   File Name:	elf.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:36:20 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_ELF_H
#define	_ELF_H

#include<beta/types.h>

typedef	__u16	Elf32_Half;
typedef	__u32	Elf32_Word;
typedef	__s32	Elf32_Sword;
typedef	__u64	Elf32_Xword;
typedef	__s64	Elf32_Sxword;
typedef	__u32	Elf32_Addr;
typedef	__u32	Elf32_Off;
typedef	__u16	Elf32_Section;
typedef	Elf32_Half	Elf32_Versym;

/*
 *--------------------------------------------------------------------------
 * ELF file Header.
 * This appears at the start of every ELF file.
 *--------------------------------------------------------------------------
 */

#define	EI_NIDENT	(16)
typedef	struct
{
	unsigned char	e_ident[EI_NIDENT];
	Elf32_Half	e_type;
	Elf32_Half	e_machine;
	Elf32_Word	e_version;
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;
	Elf32_Half	e_ehsize;	// ELF Header Size in bytes 
	Elf32_Half	e_phentsize;	// Program header table entry size
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;	//Section Header String Table Index
}Elf32_Ehdr, *pElf32_Ehdr;

#define	ELFMAG			"\177ELF"
#define	SELFMAG			4

#define	EI_MAG0			0
#define		ELFMAG0		0x7F

#define	EI_MAG1			1
#define		ELFMAG1		'E'

#define	EI_MAG2			2
#define		ELFMAG2		'L'

#define	EI_MAG3			3
#define		ELFMAG3		'F'

#define	EI_CLASS		4
#define		ELFCLASSNONE	0
#define		ELFCLASS32	1
#define		ELFCLASS64	2
#define		ELFCLASSNUM	3

#define	EI_DATA			5
#define		ELFDATANONE	0
#define		ELFDATA2LSB	1	/* 2's complement, little endian */
#define		ELFDATA2MSB	2	/* 2's complement, big endian */
#define		ELFDATANUM	3

#define	EI_VERSION		6	/* value must be EV_CURRENT */

#define	EI_OSABI		7	
#define 	ELFOSABI_NONE		0	/* UNIX System V ABI */
#define 	ELFOSABI_SYSV		0	/* Alias.  */
#define 	ELFOSABI_HPUX		1	/* HP-UX */
#define 	ELFOSABI_NETBSD		2	/* NetBSD.  */
#define 	ELFOSABI_LINUX		3	/* Linux.  */
#define 	ELFOSABI_SOLARIS	6	/* Sun Solaris.  */
#define 	ELFOSABI_AIX		7	/* IBM AIX.  */
#define 	ELFOSABI_IRIX		8	/* SGI Irix.  */
#define 	ELFOSABI_FREEBSD	9	/* FreeBSD.  */
#define 	ELFOSABI_TRU64		10	/* Compaq TRU64 UNIX.  */
#define 	ELFOSABI_MODESTO	11	/* Novell Modesto.  */
#define 	ELFOSABI_OPENBSD	12	/* OpenBSD.  */
#define 	ELFOSABI_ARM		97	/* ARM */
#define 	ELFOSABI_STANDALONE	255	/* Standalone (embedded) application */

#define	EI_ABIVERSION		8

#define	EI_PAD			9


/* values for e_type (object file type). */
#define	ET_NONE		0	/* No file type */
#define	ET_REL		1	/* Relocatable file */
#define	ET_EXEC		2	/* Executable file */
#define	ET_DYN		3	/* Shared object file */
#define	ET_CORE		4	/* Core file */
#define	ET_NUM		5	/* Number of defined types */
#define	ET_LOOS		0xFE00	/* OS-Specific range start */
#define	ET_HIOS		0xFEFF	/* OS-Specific range end */
#define	ET_LOPROC	0xFF00	/* Processor-Specific range start */
#define	ET_HIPROC	0xFFFF	/* Processor-Specific range end */

#define	EM_NONE		0	/* No Machine */
#define	EM_386		3	/* Intel 80386 */
#define	EM_MIPS		8	/* MIPS R3000 big endian*/
#define	EM_MIPS_RS3_LE	8	/* MIPS R3000 little endian*/
#define	EM_PPC		20	/* Power PC */
#define	EM_ARM		40	/* ARM */
#define	EM_NUM		95


/* values for e_version */
#define	EV_NONE		0
#define	EV_CURRENT	1
#define	EV_NUM		2
/*
 *--------------------------------------------------------------------------
 * Section header
 *--------------------------------------------------------------------------
 */
typedef	struct
{
	Elf32_Word	sh_name;	/* Section name(string tbl index) */
	Elf32_Word	sh_type;	/* Section type */
	Elf32_Word	sh_flags;	/* Section flags */
	Elf32_Addr	sh_addr;	/* virtual addr at execution */
	Elf32_Off	sh_offset;	/* Section file offset */
	Elf32_Word	sh_size;	/* Section size in bytes */
	Elf32_Word	sh_link;	/* Link to another section */
	Elf32_Word	sh_info;	/* Additional section infomation */
	Elf32_Word	sh_addralign;	/* Section alignment */
	Elf32_Word	sh_entsize;	/* Entry size if section holds tbl*/
} Elf32_Shdr, *pElf32_Shdr;


/*
 *--------------------------------------------------------------------------
 * Program segment header
 *--------------------------------------------------------------------------
 */

typedef struct
{
	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;
} Elf32_Phdr,*pElf32_Phdr;

/* p_type */
#define	PT_NULL		0	/* Program header table entry unused */
#define	PT_LOAD		1	/* Loadable program segment */
#define	PT_DYNAMIC	2	/* Dynamic linking information */
#define	PT_INTERP	3	/* Program interpreter */
#define	PT_NOTE		4	/* Auxiliary information */
#define	PT_SHLIB	5	/* Reserved */
#define	PT_PHDR		6	/* Entry for header table itself */
#define	PT_TLS		7	/* Thread-local storage segment */
#define	PT_NUM		8	/* Number of defined types */
#define	PT_LOOS		0x60000000	/* Start of OS-Specific */
#define	PT_GNU_EH_FRAME	0x6474E550	/* GCC .eh_frame_hdr segment */
#define	PT_GNU_STACK	0x6474E551	/* Indicates stack executability */
#define	PT_GNU_RELRO	0x6474E552	/* Read-only after relocation */
#define	PT_LOSUNW	0x6FFFFFFA
#define	PT_SHNWBSS	0x6FFFFFFA	/* Sun Specific Segment */
#define	PT_SUNWSTACK	0x6FFFFFFB	/* Stack segment */
#define	PT_HISUNW	0x6FFFFFFF
#define	PT_HIOS		0x6FFFFFFF	/* End of OS-Specific */
#define	PT_LOPROC	0x70000000	/* Start of processor-specific */
#define	PT_HIPROC	0x7FFFFFFF	/* End of processor-specific */


#endif //_ELF_H
