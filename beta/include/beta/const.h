/*
 *--------------------------------------------------------------------------
 *   File Name:	const.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Oct  1 23:52:30 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_CONST_H
#define	_CONST_H



#define	NGDT	(16)
#define	NIDT	(256)


#define	INTR_GATE	0x0E
#define	TRAP_GATE	0x0F
#define	TSS_DESC	0x09

#define	PRI_KRNL	0x00
#define	PRI_TASK	0x00
#define	PRI_USER	0x03

#define	INX_KCS	0x01
#define	INX_KDS	0x02
#define	INX_UCS	0x03
#define	INX_UDS	0x04
#define	INX_TSS	0x05

#define	SELECTOR_KRNL_CS	(INX_KCS*8)
#define	SELECTOR_KRNL_DS	(INX_KDS*8)
#define	SELECTOR_USER_CS	(INX_UCS*8)
#define	SELECTOR_USER_DS	(INX_UDS*8)
#define	SELECTOR_TSS		(INX_TSS*8)
#define	SELECTOR_KRNL_SS	SELECTOR_KRNL_DS
#define	SELECTOR_USER_SS	SELECTOR_USER_DS


#define	KRNL_CS			(SELECTOR_KRNL_CS | PRI_KRNL)
#define	KRNL_DS			(SELECTOR_KRNL_DS | PRI_KRNL)
#define	USER_CS			(SELECTOR_USER_CS | PRI_USER)
#define	USER_DS			(SELECTOR_USER_DS | PRI_USER)




#endif //_CONST_H
