/*
 *--------------------------------------------------------------------------
 *   File Name:	utility.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Oct  6 18:43:56 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#define	VERSION "0.0"
const char *version =
"Beta "	VERSION " Released at " __DATE__ " " __TIME__ ;

void assert_fail(char *exp, char *file, unsigned int line, char *func)
{
	kprintf("%s:%d: %s: Assertion \'%s\' failed.\n",
		file, line, func, exp);

	while(1);
}
