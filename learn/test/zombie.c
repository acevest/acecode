/*
 *--------------------------------------------------------------------------
 *   File Name:	zombie.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Apr 16 10:56:48 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void wait4children(int signo) {
	int status;
	while(waitpid(-1, &status, WNOHANG) > 0);
}

int main() {

	int i;
	pid_t pid;

	signal(SIGCHLD, wait4children);

	for(i=0; i<100; i++) {
		pid = fork();
		if(pid == 0)
			break;
	}

	if(pid>0) {
		printf("press Enter to exit...");
		getchar();
	}

	return 0;
}
