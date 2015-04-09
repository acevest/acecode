/*
 * ------------------------------------------------------------------------
 *   File Name: of.1.c
 *      Author: Zhao Yanbai
 *              Thu Apr  9 18:50:29 2015
 * Description: 
 *              gcc of.1.c  -fno-stack-protector
 * ------------------------------------------------------------------------
 */
#include<stdio.h>
#include<string.h>

const char *pwd = "1234";

int of(const char *s)
{
    int r = 0xFEDCBA98;
    char buf[8];
    
    r = strcmp(pwd, s) == 0 ? 1 : 0;

    __builtin___strcpy_chk(buf, s, 1000);

    return r;
}

int main(int argc, char *argv[]){

    char buf[256];

    scanf("%s", buf);

    if(of(buf))
    {
        printf("SUCC:  %s\n", buf);
    }
    else
    {
        printf("FAIL:  %s\n", buf);
    }

	return 0;
}
