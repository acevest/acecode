/*
 * ------------------------------------------------------------------------
 *   File Name: init.c
 *      Author: Zhao Yanbai
 *              Sun Apr  1 19:13:23 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

int main() {
	int beta_sysenter();
	int ret;
    int beta_notify();
	while(1){
		asm(""::"a"(1),"b"(2),"c"(3),"d"(4),"D"(5));
		ret = beta_sysenter();
		asm(""::"a"(ret));
		//asm("xchg %bx,%bx;");
        int i = 100000;
        while(i--);
        beta_notify();
        //asm("cli;sti;"); // should be error
	}
    return 0;
}
