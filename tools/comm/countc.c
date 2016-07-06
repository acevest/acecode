/*
 * count.c (C) Zhao Yanbai
 * 2007-09-21
 *
 * this program is used to count the program lines of 
 * all files that in the file
 *
 * this version is more quickly.
 * because i let the program deal with the path more easily.
 * 
 * Version 1.1
 */
/*
 * Version 1.2	2008.11.11 20:59
 * Version 1.3	2008.12.17 22:53
 * Version 1.4	2010.10.15 14:11
 */

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>

void	count_dir(char	*path);
void	count_file(char *path);
int	valid_type(char *name,char *type);
char	*get_type(char	*name);
long	total_line	= 0;
int	file_num	= 0;
long	total_bytes	= 0;


int	main(int argc,char *argv[])
{
	int	i;
	if(argc <= 2){printf("parameter error\n");return -1;}
	++argv;
	printf("[line] [ byte ] path\n");
	if(!strcmp(*argv,"-d"))		count_dir(*++argv);
	else if(!strcmp(*argv,"-f"))	count_file(*++argv);
	else{printf("parameter error\n");return -1;}
	printf("+-------------------------------+\n");
	printf("| %10d Files.             |\n",file_num);
	printf("| %10ld Lines.             |\n",total_line);
	printf("| %10ld bytes.             |\n",total_bytes);
	printf("+-------------------------------+\n");
}

void	count_dir(char	*path)
{
	DIR	*pdir;
	struct	dirent	*pdirent;
	int	len_path = strlen(path);
	//char	path_t[500];
	if( (pdir = opendir(path)) )
	{
		while( (pdirent = readdir(pdir)) )
		{
			if(pdirent->d_name[0] == '.')	continue;
			//strcpy(path_t,path);
			strcat(strcat(path,"/"),pdirent->d_name);
			if(pdirent->d_type == 4)	//dir
			{
				count_dir(path);
			}
			else if(pdirent->d_type == 8)
			{
				count_file(path);
			}
			path[len_path]=0;
		}

		closedir(pdir);
	}
}

void	count_file(char	*path)
{
	FILE	*fp;
	int	line=0;
	char	ch;

#if 1
	if(!valid_type(path,"c") && !valid_type(path,"cc") && !valid_type(path,"h")
	&& !valid_type(path,"asm") && !valid_type(path,"inc")
	&& !valid_type(path,"cpp")
	&& !valid_type(path,"S") && !valid_type(path,"s")
	&& !valid_type(path,"pl")
	&& !valid_type(path,"py")
	&& !valid_type(path,"rb")
	&& !valid_type(path,"go")
	&& !valid_type(path,"php")
	&& !valid_type(path,"asp")
	&& !valid_type(path,"jsp")
	&& !valid_type(path,"swift")
	)
	{
#if 0
		printf("[%4d] %-50s\n",line,path);
#endif
		return;
	}
#endif

	struct stat st;
	if(stat(path, &st) != -1)
		total_bytes += st.st_size;


	if( (fp = fopen(path,"r")) )
	{
		while(!feof(fp))
		{
			ch	= fgetc(fp);
			if(ch == '\n'){total_line++;line++;}
		}
		printf("[%4d] [%6lld] %-50s\n",line, st.st_size, path);
		file_num++;
		fclose(fp);
	}
	else
	{
		printf("can not open file: %s\n",path);
		perror("reason");
	}

}

int valid_type(char *name,char *type)
{
	int	len_name,len_type,i;
	char	ftype[20];
	if(type[0] == '*') return 1;
	len_type = strlen(type);
	len_name = strlen(name);

	if(len_type == 0)
	{
		for(i=len_name-1;i>=0;i--)
			if(name[i] == '.')	return 0;
		return 1;
	}

	return ( !(strcmp(name+len_name-len_type,type)) && (name[len_name-len_type-1] == '.'));
}
