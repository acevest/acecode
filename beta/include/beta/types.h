/*
 *--------------------------------------------------------------------------
 *   File Name:	types.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct 16 13:33:00 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_TYPES_H
#define	_TYPES_H

typedef	unsigned char		__u8;
typedef	unsigned short		__u16;
typedef	unsigned int		__u32;
typedef	unsigned long long	__u64;

#define	__bitwise__	__attribute__((bitwise))


typedef	__u16	__bitwise__	__le16;
typedef	__u16	__bitwise__	__be16;
typedef	__u32	__bitwise__	__le32;
typedef	__u32	__bitwise__	__be32;
typedef	__u64	__bitwise__	__le64;
typedef	__u64	__bitwise__	__be64;


#endif //_TYPES_H
