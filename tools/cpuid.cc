/*
 * 	获取CPU信息的程序
 * 	Wed Dec 05 2007 by Zhao Yanbai [Create]
 *	Thu May 29 2008 by Zhao Yanbai
 *	Version 0.2
 *
 */

#include<iostream>
#include<memory.h>
using namespace std;

#define	SET_BIT(bit) (1UL<<bit)
#define	CLR_BIT(bit) (~(1UL<<bit))
#define	ISSET_BIT(val,bit) ((val) & SET_BIT(bit))
#define	TEST_FEATURE(val,bit,fea)\
do{\
	if( ISSET_BIT(val,bit) )\
		cout<<"\t[Y] "<<fea<<endl;\
	else\
		cout<<"\t[N] "<<fea<<endl;\
}while(0);

typedef struct reg{ unsigned long eax,ebx,ecx,edx; }Reg,*pReg;
Reg	cpuid(unsigned long op)
{
	Reg	r;
	asm("cpuid;"
	:"=a"(r.eax),
	 "=b"(r.ebx),
	 "=c"(r.ecx),
	 "=d"(r.edx)
	:"a"(op)
	);

	return 	r;
}


int	main()
{

	Reg	r;
	unsigned short int cpu_sn[6];	//serial number
	int	i;

	/**********************Get CPU Name********************************/
	char	cpu_name[13];
	r=cpuid(0);
	memcpy(cpu_name + 0, &r.ebx, 4);
	memcpy(cpu_name + 4, &r.edx, 4);
	memcpy(cpu_name + 8, &r.ecx, 4);
	cpu_name[12] = 0;
	cout<<"CPU Name: "<<cpu_name<<endl;

 	/**********************Get Processor Brand String******************/
	char	pbs[50];		//processor brand string
	r = cpuid(0x80000002);
	memcpy(pbs + 0 , &r.eax, 4);
	memcpy(pbs + 4 , &r.ebx, 4);
	memcpy(pbs + 8 , &r.ecx, 4);
	memcpy(pbs + 12, &r.edx, 4);
	r=cpuid(0x80000003);
	memcpy(pbs + 16 , &r.eax, 4);
	memcpy(pbs + 20 , &r.ebx, 4);
	memcpy(pbs + 24 , &r.ecx, 4);
	memcpy(pbs + 28 , &r.edx, 4);
	r=cpuid(0x80000004);
	memcpy(pbs + 32 , &r.eax, 4);
	memcpy(pbs + 36 , &r.ebx, 4);
	memcpy(pbs + 40 , &r.ecx, 4);
	memcpy(pbs + 44 , &r.edx, 4);
	cout<<pbs<<endl;

 	/**********************Get Number of Processors********************/
	int	pn;//number of logical processors in one physical processor
	r=cpuid(1);
	pn	= ((r.ebx & 0x00FF0000) >> 16);
	cout<<"Number of Processors:"<<pn<<endl;
  
 	/**********************Get the CPU's Feature***********************/
	int	fv = r.edx;
	TEST_FEATURE(fv, 1, "FPU on chip")
	TEST_FEATURE(fv, 2, "VME: Virtual-8086 Mode enhancements")
	TEST_FEATURE(fv, 3, "DE: Debug Extensions (I/O breakpoints)")
	TEST_FEATURE(fv, 4, "PSE: Page Size Extensions")
	TEST_FEATURE(fv, 5, "MSR: RDMSR and WRMSR support")
	TEST_FEATURE(fv, 6, "PAE: PHYSICAL Address Extensions")
	TEST_FEATURE(fv, 7, "MCE: Machine Check Exception")
	TEST_FEATURE(fv, 8, "CXS: CMPXCHG8B instruction")
	TEST_FEATURE(fv, 9, "APIC: APIC on Chip")
	//TEST_FEATURE(fv, 10, "Reserved")
	TEST_FEATURE(fv, 11, "SYSENTER/SYSEXIT support")
	TEST_FEATURE(fv, 12, "MTRR: Memory Type Range Reg")
	TEST_FEATURE(fv, 13, "PGE/PTE Global Bit")	
	TEST_FEATURE(fv, 14, "MCA: Machine Check Architecture")
	TEST_FEATURE(fv, 15, "CMOV: Cond mov/cmp Instructions")
	TEST_FEATURE(fv, 16, "PAT: Page Attribute Table")
	TEST_FEATURE(fv, 17, "PSE-36: Physical Address Extensions")
	TEST_FEATURE(fv, 18, "Processor Serial Number")
	TEST_FEATURE(fv, 19, "CLFLUSH: CLFLUSH Instruction support")
	//TEST_FEATURE(fv, 20, "Reserved")
	TEST_FEATURE(fv, 21, "DS: Debug Store")
	TEST_FEATURE(fv, 22, "ACPI: Thermal Monitor and Software "
				"Controlled Clock Facilities")
	TEST_FEATURE(fv, 23, "MMX Technology")
	TEST_FEATURE(fv, 24, "FXSR: FXSAVE/FXRSTOR (also indicates "
				"CR4.OSFXSR is available)")
	TEST_FEATURE(fv, 25, "SSE: SSE Extensions")
	TEST_FEATURE(fv, 26, "SSE2: SSE2 Extensions")
	//TEST_FEATURE(fv, 27, "Reserved")
	TEST_FEATURE(fv, 28, "Hyper Threading Technology")
	TEST_FEATURE(fv, 29, "TM: Thermal Monitor")
	//TEST_FEATURE(fv, 30, "Reserved")
	TEST_FEATURE(fv, 31, "PBE: Pending Break Enable")



	




 	/**********************Get CPU's SERIAL Number*********************/
/*	r=cpuid(1);
	printf("%x\n",r.edx);
	

	//get serial number
	r=cpuid(1);
	memcpy((&cpu_sn) + 4, &r.eax, 4);
	if(r.edx & (1<<18))
	{

		r=cpuid(3);
		memcpy((&cpu_sn) + 0, &r.ecx, 8);
		for(i=5;i>=0;i--)
		{
			printf("%x",cpu_sn[i]);
			if(i)	printf("-");
		}
		printf("\n");
	}*/


	return 0;
}
