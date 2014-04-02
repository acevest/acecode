/*
 *--------------------------------------------------------------------------
 *   File Name:	list.h
 * 
 * Description:	none
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Mon Apr 20 20:52:05 2009
 * Last Update: Mon Apr 20 20:52:05 2009
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_LIST_H
#define	_LIST_H

/* Allmost Copy From Linux */
typedef struct list_head
{
	struct list_head *prev, *next;
} ListHead, *pListHead;

#define	LIST_HEAD_INIT(name) {&(name), &(name) }
#define	LIST_HEAD(name) ListHead name = LIST_HEAD_INIT(name)
#define	INIT_LIST_HEAD(ptr) 		\
do{					\
	(ptr)->next = (ptr);		\
	(ptr)->prev = (ptr);		\
}while(0)

#define	list_entry(ptr, type, member)	\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define	list_for_each(pos, head)	\
	for(pos = (head)->next; pos != (head); pos = pos->next)
#define	list_for_each_safe(pos, tmp, head)		\
	for(pos = (head)->next, tmp = pos->next;	\
		pos != (head);				\
		pos = tmp, tmp = pos->next)

static inline void _list_add(	pListHead newItem,
				pListHead prev,
				pListHead next)
{
	next->prev	= newItem;
	newItem->next	= prev->next;
	newItem->prev	= prev;
	prev->next	= newItem;
}

static inline void list_add(pListHead newItem, pListHead head)
{
	_list_add(newItem, head, head->next);
}

static inline void list_add_tail(pListHead newItem, pListHead head)
{
	_list_add(newItem, head->prev, head);
}


static inline void _list_del(pListHead prev, pListHead next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(pListHead entry)
{
	_list_del(entry->prev, entry->next);
}

static inline void list_del_init(pListHead entry)
{
	_list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

static inline int list_is_empty(pListHead head)
{
	return head->next == head;
}


#endif //_LIST_H
