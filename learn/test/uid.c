/*
 * ------------------------------------------------------------------------
 *   File Name: uid.c
 *      Author: Zhao Yanbai
 *              Wed Apr 11 15:11:43 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char *argv[]){

    uid_t uid;

    uid = getuid();

    if(uid == 0) {
        printf("This is root\n");
        setuid(65534);
    } else {
        printf("This is not root\n");
    }

	return 0;
}
