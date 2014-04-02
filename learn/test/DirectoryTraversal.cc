/*
 *--------------------------------------------------------------------------
 *   File Name:	DirectoryTraversal.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Aug 30 13:39:00 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<sys/types.h>
#include<dirent.h>
#include<cassert>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

void DirectoryTraversal(char *dpath, void (*func)(char *file))
{
	DIR	*pdir;
	struct dirent *pent;
	char	path[1024];
	int	len;

	pdir = opendir(dpath);
	if(pdir == NULL)
		return;

	strcpy(path, dpath);
	strcat(path, "/");
	len = strlen(path);
	assert(len < 1024);

	while((pent=readdir(pdir)) != NULL)
	{
		if(strcmp(pent->d_name, ".") == 0
		|| strcmp(pent->d_name, "..") == 0)
			continue;

		path[len] = 0;
		strcat(path, pent->d_name);

		if(pent->d_type == DT_DIR)
		{
			DirectoryTraversal(path, func);
		}
		else if(pent->d_type == DT_REG)
		{
			func(path);
		}
	}
}

void handle(char *file)
{
	cout<<file<<endl;
}

int main()
{
	char d[]="libpps";
	DirectoryTraversal(d, handle);

	return 0;
}
