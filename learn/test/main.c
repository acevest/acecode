/*
 * ------------------------------------------------------------------------
 *   File Name: main.c
 *      Author: Zhao Yanbai
 *              Wed Jul  9 23:28:56 2014
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<stdio.h>

int main(int argc, char *argv[], char *env[]) {
    unsigned int i;
    for(i=0; env[i]; ++i)
        printf("env[%u] %s\n", i, env[i]);

	return 0;
}
