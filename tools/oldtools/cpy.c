/*
 *--------------------------------------------------------------------------
 *   File Name:	cpy.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Jun 30 11:22:16 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int	fd;
	time_t	now;
	char timestr[256];
	char cmd[]	= "#!/usr/bin/env python\n";
	char charset[]	= "# -*- coding: utf-8 -*-\n";
	char line[]	= "# -------------------------------------"
			  "-------------------------------------\n";
	char file[]	= "#   File Name:\t";
	char author[]	= "\n#      Author:\tZhao Yanbai\n#\t\t";
	char desc[]	= "# Description:\tnone\n";

	if(argc != 2)
	{
		printf("usage: %s <file.py>\n", argv[0]);
		exit(1);
	}

	now = time(NULL);
	strcpy(timestr, ctime(&now));

	fd = open(argv[1], O_CREAT | O_WRONLY,
		S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	write(fd, cmd, strlen(cmd));
	write(fd, charset, strlen(charset));
	write(fd, line, strlen(line));
	write(fd, file, strlen(file));
	write(fd, argv[1], strlen(argv[1]));
	write(fd, author, strlen(author));
	write(fd, timestr, strlen(timestr));
	write(fd, desc, strlen(desc));
	write(fd, line, strlen(line));
	
	close(fd);
	return 0;
}
