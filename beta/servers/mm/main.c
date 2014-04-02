/*
 * ------------------------------------------------------------------------
 *   File Name: init.c
 *      Author: Zhao Yanbai
 *              Sun Apr  1 19:13:23 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

int main() {
	while(1){
        int i = 100000;
        while(i--);
        asm("cli;sti;");    // for privilage test
	}
    return 0;
}
