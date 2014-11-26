#include<iostream>
#include<string>
#include<sys/wait.h>
#include<string.h>
#include"Ish.h"
#include"Cmd.h"
#include"Common.h"
#include"Scanner.h"
#include"Parser.h"
#include"Debug.h"
using namespace std;


//#ifdef	DEBUG_MAIN
int main(int argc,char *argv[])
{
	Parser p;
	if(argc >= 3) return 0;
	if(argc == 2)
	{
		StringBuffer scriptfile;
		scriptfile.setString(argv[1]);
		p.setInputFile(scriptfile.getString());
	}
	p.beginParser();
	return 0;
}
//#endif
