/*
 *--------------------------------------------------------------------------
 *   File Name:	pipe.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Apr 15 20:33:36 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

	int pid;
	int fd[2];	// read on fd[0] write on fd[1]

	if(pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();

	if(pid < 0) {
		perror("failed to create child...");
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		char ch;
		close(fd[1]);
		while(read(fd[0], &ch, sizeof(ch)) > 0) {
			printf("%c", ch);
		}
		close(fd[0]);
		exit(EXIT_SUCCESS);
	} else {
		char msg[] = "test pipe ...\n";
		close(fd[0]);
		write(fd[1], msg, strlen(msg));
		close(fd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
