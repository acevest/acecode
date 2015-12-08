#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include"Common.h"
#include"Cmd.h"
#include"Debug.h"
#include"Parser.h"
#include"Ish.h"
/*************Static******************/
const char *cmd::m_delimiters=" \t";

/*************************************/
cmd::cmd():m_cmd_buf(NULL),m_buf_size(CMD_BUF_SIZE),m_buf_pos(0)
{
}
cmd::~cmd()
{
}


//affter invoked this function,do not forget to call freemakeargv();
int cmd::makeargv(const char *cmd_buf,char ***argvp,const char *delimiters)
{
	if( (cmd_buf == NULL) || (delimiters == NULL) || (argvp == NULL) )
		return -1;
	*argvp = NULL;		//for safe...
	const char *snew = cmd_buf + strspn(cmd_buf, delimiters);	//Ignore the front delimiters of line...
	char *t;
	if( (t = (char *)(new char [strlen(snew) + 1])) == NULL )
		return -1;

	//count	parmeters
	strcpy(t, snew);
	int	numtokens = 0;
	if(strtok(t, delimiters) != NULL)
		for(numtokens = 1; strtok(NULL, delimiters) != NULL;)
			numtokens++;

	
	if((*argvp = (char **)(new char [(numtokens +1)*sizeof(char *)])) == NULL)
	{
		free(t);
		return -1;
	}

	if(numtokens == 0)
		free(t);
	else
	{
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for(int i=1; i<numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}

	//for safe...
	*((*argvp) + numtokens) = NULL;

	
	return numtokens;
}

//must call it by yourself...
void cmd::freemakeargv(char **argv)
{
//	if(argv == NULL)	return ;
//	if(*argv != NULL)
//		free(*argv);
//	free(argv);
	//int i=0;
	//while(argv[i])
	//	free(argv[i++]);
	//free(&argv);
}

#include<iostream>
using namespace std;
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char *cmd::get_cmd(FILE *fp)
{
	char ch;

	m_buf_pos = 0;

	m_cmd_buf = new char[m_buf_size];/*(char *)my_malloc(m_buf_size);*/

	fgets(m_cmd_buf,m_buf_size,fp);

	int len	= strlen(m_cmd_buf);

	if(len>0 && m_cmd_buf[len-1] == '\n')
	{
		m_cmd_buf[len-1] = 0;
	}
	else
	{
		printf("Error in Get CMD...\n");
		exit(1);
	} 

/*	while( (ch = getc(fp)) != EOF)
	{
		if( m_buf_size <= (m_buf_pos+1) )
		{
	
		}		
	}*/

	return m_cmd_buf;
}
void cmd::disp_cmd() const
{
	cout<<m_cmd_buf<<endl;
}

ExitCode cmd::ExecuteCommand(char **argv)
{

	//while(true)
	//{
		//shell.disp_cmd_prompt();

		if( strcmp(argv[0],"exit") == 0 ) exit(0);
		
		//char *arglist[10];
		//arglist[0]=NULL;
		pid_t cpid;
		cpid = fork();
		if(cpid == -1)
		{
			perror("Faild to Create Process...");
			return 1;
		}
		if(cpid == 0)
		{
			int fd,newfd;
			//cout<<argv[0]<<endl;
			if(g_redirectInFlag)
			{
				fd = open(g_redirectFile.getString(),O_WRONLY | O_CREAT);
				close(0);
				newfd = dup(fd);
				close(fd);
			}
			if(g_redirectOutFlag)
			{
				fd = open(g_redirectFile.getString(),O_WRONLY | O_CREAT);
				close(1);
				newfd = dup(fd);
				close(fd);
			}
			execvp(argv[0],/*NULL*/argv);
			perror("unknow commond."/*"Child faild to execvp the command"*/);
			return 1;
		}
		if(cpid != wait(NULL))
		{
			perror("Parent failed to wait");
			return 1;
		}

	//}

	return 0;
}

#ifdef	DEBUG_CMD
int main()
{
	cmd c;
	char **argv;
	c.get_cmd();
	c.disp_cmd();
	int a=c.makeargv(&argv);
	cout<<a<<endl;
	for(int i=0;i<a;i++)
		cout<<"cmd["<<i<<"]:"<<argv[i]<<endl;
	return 0;
}
#endif
