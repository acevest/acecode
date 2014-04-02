#include<unistd.h>
#include<stdio.h>
#include<pwd.h>
#include<string>
#include<string.h>
#include<sys/wait.h>
#include<iostream>

using namespace std;

#include"Ish.h"
#include"Debug.h"
#include"Variables.h"

ish shell;




ish::ish()
{
	init_shell_environment();
	init_cmd_prompt();
}
ish::~ish()
{
//	cout<<"bye bye~~~~~~"<<endl;
}

char * ish::get_user() const
{
	return m_user;
}
void ish::disp_cmd_prompt() const
{
	cout<<m_cmd_prompt;
}
#include<stdlib.h>
void ish::init_shell_environment()
{
	//current user...
//	struct passwd *p = getpwuid(geteuid());
//	m_username = (char *) (p->pw_name);

    	//current path
//	m_pwd = p->pw_dir;
//	cout<<"===="<<m_pwd<<endl;

	extern char **environ;
	for(int i=0; environ[i] != NULL; i++)
	{
		char name[255];
		int j = 0;
		while(environ[i][j] != '=')
		{
			name[j] = environ[i][j];
			j++;
		}
		name[j] = 0;

		g_variables.storeVariable(name,environ[i] + j + 1);

#ifdef	SHOW_ENV
		cout<<name<<"\n\t"<<g_variables.getVariable(name)<<endl;
#endif
	}
	m_user		= getenv("USER");
	m_pwd		= getenv("PWD");
	m_path		= getenv("PATH");
	m_hostname	= getenv("HOSTNAME");
#ifdef	DEBUG_SHELL_ENV
	cout<<"m_user:"<<m_user<<endl;
	cout<<"m_pwd:"<<m_pwd<<endl;
	cout<<"m_path:"<<m_path<<endl;
	cout<<"m_hostname:"<<m_hostname<<endl;
#endif
}
void ish::init_cmd_prompt()
{
	m_cmd_prompt = "[" + (string) get_user() + "]";
	if(strcmp(get_user(),"root") == 0)
		m_cmd_prompt +="#";
	else
		m_cmd_prompt +="$";

}
