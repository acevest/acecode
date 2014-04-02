/*
 *--------------------------------------------------------------------------
 *   File Name:	elf.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Jul 25 15:08:19 2009
 * 
 * Description:	分析ELF文件。
 * 		这段代码以后会被整合到我的内核中。
 * 
 *--------------------------------------------------------------------------
 */
#include<sys/types.h>
#include<sys/mman.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#define	printk	printf		// For My Kernel

typedef	unsigned short		s16;
typedef	unsigned int		s32;
typedef	unsigned long long	s64;
typedef	short		u16;
typedef	int		u32;
typedef	long long	u64;
#if 1
typedef	u16	Elf32_Half;
typedef	u16	Elf32_Word;
typedef	s16	Elf32_Sword;
typedef	u64	Elf32_Xword;
typedef	s64	Elf32_Sxword;
typedef	u32	Elf32_Addr;
typedef	u32	Elf32_Off;
typedef	u16	Elf32_Section;

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
	Elf32_Half	e_ehsize;	//ELF Header Size
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;	//Section Header String Table Index
}Elf32_Ehdr;
#endif

int main(int argc, char *argv[])
{
	struct	stat	fst;
	int 	fd;
	int	i;
	const	char *fn = argv[1];
	const	char *map = NULL;
	unsigned char	*pf = NULL;

	if(argc != 2)
	{
		printk("parameters error...\n");
		return 0;
	}

	fd = open(fn,O_RDONLY);
	if(-1 == fd)
	{
		perror("open");
		return 0;
	}
	if(-1 == fstat(fd, &fst))
	{
		perror("fstat");
		return 0;
	}

	map = (const char *)mmap(NULL, fst.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	pf = (char *)map;
	Elf32_Ehdr *pEhdr = (Elf32_Ehdr *) pf;



	// 程序尚未完成，等待在这儿添加分析代码
	for(i=0; i<100; i++)
		printf("%02x ", pf[i]);


	printf("\n");

	return 0;
}
