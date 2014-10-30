/*
 * ------------------------------------------------------------------------
 *   File Name: htn.c
 *      Author: Zhao Yanbai
 *              Sat Jul 12 17:00:31 2014
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<stdio.h>

int main(int argc, char *argv[]){
	unsigned int ch;
	while(scanf("%x",&ch) != EOF)
		printf("%u\n",ch);

	return 0;
}
