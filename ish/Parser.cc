/*
 * Parser.cc (C) Zhao Yanbai
 *
 * Sat Jul 12 16:53 2008
 */
#include"Debug.h"
#include"Parser.h"
#include"StringBuffer.h"
#include"Cmd.h"
#include"Ish.h"
#include<string.h>
#include<iostream>
using namespace std;
//============================
//gloabl variable
//============================
StringBuffer g_redirectFile;
bool g_redirectInFlag;
bool g_redirectOutFlag;
cmd g_command;

Parser::Parser():m_errorFlag(false)
{
#ifdef DEBUG_PARSER
	cout<<"Parser()"<<endl;
#endif
	g_redirectFile.setString("file");
	bool g_redirectInFlag = false;
	bool g_redirectOutFlag = false;
}
Parser::~Parser()
{
#ifdef DEBUG_PARSER
	cout<<"~Parser()"<<endl;
#endif
}
/*
TokenType Parser::getToken()
{
	TokenType t = m_scanner.getToken();
	return t;	
}
int Parser::getCurrentLine() const
{
	return m_scanner.getCurrentLine();
}*/
void Parser::syntaxError(const char *s)
{
	fprintf(stderr,"syntax error at line:%d: %s\n",
		getCurrentLine(),s);
	m_errorFlag = true;
}
void Parser::match(TokenType e)
{
#ifdef DEBUG_PARSER_STATEMENT
	cout<<"match:";
#endif
	if(m_token == e)
	{
	//	printToken(m_token);
		m_token = getToken();
	}
	else
	{
		syntaxError("unexpected token");
		cout<<"match error:--->";
		printToken(m_token);
	}
}

bool Parser::isControlCmd() const
{
	return ( m_token == IF || m_token == WHILE);
}

void Parser::IfStatement()
{
#ifdef DEBUG_PARSER_STATEMENT
	cout<<"IfStatement()"<<endl;
#endif
	ExitCode e;
	match(IF);
	switch(m_token)
	{
	case LSB:
		match(LSB);
		e = Exp();
		match(RSB);
		goto ifthennextpart;
	case STRING:
		e = ExecuteCmd();
ifthennextpart:
		match(THEN);
		if(e == 0)
		{
			//printToken(m_token);
			SequenceStatement();
			//ignor else part...
			int flag = 0;
			//while(m_token !=FI || flag != 0)
			while(true)
			{
				if(m_token == FI && flag == 0)
					break;
				if(m_token == IF)
					flag++;
				else if(m_token == FI)
					flag--;
				m_token = getToken();
			}
		}
		else
		{
			//ignore then part...
			int flag = 0;
			//while((m_token != ELSE || m_token != FI)
			//	 || flag != 0)
			while(true)
			{
				if(m_token == ELSE && flag == 0)
					break;
				if(m_token == FI && flag == 0)
					break;

				if(m_token == IF)
					flag++;
				else if(m_token == FI)
					flag--;
				m_token = getToken();

			}
			if(m_token == ELSE)
			{
				match(ELSE);
				SequenceStatement();
			}

		}

		match(FI);
		break;
	default:
		syntaxError("if");
	}
	//Statement();
}

void Parser::WhileStatement()
{
#ifdef DEBUG_PARSER_STATEMENT
	cout<<"WhileStatement()"<<endl;
#endif
	cout<<"not support now"<<endl;
}

void Parser::AssignStatement()
{
#ifdef DEBUG_PARSER_STATEMENT
	cout<<"AssignStatement()"<<endl;
#endif
	/*int lenname = getTokenStringLen();
	char *varname = new char [lenname + 1];
	strcpy(varname,getTokenString());*/
	StringBuffer varname;
	varname.setString(getTokenString());
	StringBuffer varvalue;
	match(SETVAR);
	match(ANS);
	/*int lenvalue = getTokenStringLen();
	char *varvalue = new char [lenvalue + 1];
	strcpy(varvalue,getTokenString());*/
	//printToken(m_token);
	if(m_token == STRING)
	{
		varvalue.setString(getTokenString());
		match(STRING);
	}
	else if(m_token == GETVAR)
	{
		const char *p;
		p = g_variables.getVariable(getTokenString() + 1);
		varvalue.setString("");
		if( p != NULL )
			varvalue.setString(p);
		match(GETVAR);
	}
	//store variable...
	g_variables.storeVariable(varname.getString(),varvalue.getString());

#ifdef	DEBUG_PARSER
		cout<<"ASS-VAR:"<<g_variables.getVariable(varname.getString())<<endl;
#endif
	//Statement();
}
ExitCode Parser::ExecuteCmd()
{
#ifdef DEBUG_PARSER_STATEMENT
	cout<<"ExecuteCmd()"<<endl;
#endif

	//record current line
	int cl,tcl;
	cl = getCurrentLine();
	StringBuffer cmdstr;

	do
	{
		cmdstr.appendString(getTokenString());
		cmdstr.appendString(" ");
		match(STRING);
		tcl = getCurrentLine();
	}while(m_token == STRING && cl == tcl);

	//cout<<"COMMAND: "<<cmdstr.getString()<<endl;
	
	//printToken(m_token);
	//cout<<getTokenString()<<endl;
	if(m_token == RINS)
	{
		match(RINS);
		g_redirectInFlag = true;
		//save redirect file name...
	g_redirectFile.setString(getTokenString());
		match(REDFN);
	}
	else if(m_token == ROUTS)
	{
		match(ROUTS);
		g_redirectOutFlag = true;
		//save redirect file name...
	g_redirectFile.setString(getTokenString());
		match(REDFN);
	}
	//match(STRING);
	//cout<<">>>"<<g_redirectFile.getString()<<endl;

	char **argv;
	int n=g_command.makeargv(cmdstr.getString(),&argv);
	//for(int i=0;i<n;i++)
	//	cout<<"argv["<<i<<"]:"<<argv[i]<<endl;
	g_command.ExecuteCommand(argv);	
	//command.freemakeargv(argv);


	g_redirectInFlag = g_redirectOutFlag = false;

	return 0;
}

ExitCode Parser::Exp()
{
		/*if(m_token != STRING && m_token != GETVAR)
			syntaxError("exp() error...");
		if(m_token == STRING)
			match(STRING);
		if(m_token == GETVAR)
			match(GETVAR);*/

		const char *pt;

		StringBuffer tempvarA;
		switch(m_token)
		{
		case STRING:
			tempvarA.setString(getTokenString());
			match(STRING);
			break;
		case GETVAR:
			pt = g_variables.getVariable(getTokenString() + 1);
			tempvarA.setString("");
			if( pt != NULL )
				tempvarA.setString(pt);
			//cout<<tempvarA.getString()<<endl;
			//tempvarA.setString(g_variables.getVariable(getTokenString() + 1)); //+ 1 ignor '$'
			match(GETVAR);
			break;
		default:
			syntaxError("unexpected String or Variable in EXP");
			break;
		}

		//cout<<tempvarA.getString()<<endl;
		//while(1);

		TokenType t = m_token;
		switch(m_token)
		{
		case EQ:	match(EQ);	break;
		case NE:	match(NE);	break;
		case GT:	match(GT);	break;
		case GE:	match(GE);	break;
		case LT:	match(LT);	break;
		case LE:	match(LE);	break;
		default:
			syntaxError("incorrect Sign in EXP");
			break;
		}

		
		StringBuffer tempvarB;
		switch(m_token)
		{
		case STRING:
			tempvarB.setString(getTokenString());
			match(STRING);
			break;
		case GETVAR:
			pt = g_variables.getVariable(getTokenString() + 1);
			tempvarB.setString("");
			if( pt != NULL )
				tempvarB.setString(pt);
			//tempvarB.setString(g_variables.getVariable(getTokenString() + 1)); //+ 1 ignor '$'
			match(GETVAR);
			break;
		default:
			syntaxError("unexpected String or Variable in EXP");
			break;
		}

		const char *p,*q;
		p = tempvarA.getString();
		q = tempvarB.getString();


		while( (*p - *q) == 0 && (*p != 0) && (*q != 0))
		{
			p++;
			q++;
		}

		int e = *p - *q;

		switch(t)
		{
		case EQ:
			e = (e == 0)?0:1;
			break;
		case NE:
			e = (e != 0)?0:1;
			break;
		case GT:
			e = (e > 0)?0:1;
			break;
		case GE:
			e = (e >= 0)?0:1;
			break;
		case LT:
			e = (e < 0)?0:1;
			break;
		case LE:
			e = (e >= 0)?0:1;
			break;
		default:
			syntaxError("incorrect Sign in EXP");
			break;
		}
#ifdef	DEBUG_PARSER
		cout<<"VAR:"<<p<<endl;
		cout<<"VAR:"<<q<<endl;
		cout<<"="<<e<<endl;
#endif
		return (ExitCode) e;
}
void Parser::Statement()
{
#ifdef	DEBUG_PARSER_STATEMENT
	cout<<"Statement()"<<endl;
#endif
	//m_token = getToken();
	//printToken(m_token);
	switch(m_token)
	{
	case IF:
		IfStatement();
		break;
	case WHILE:
		WhileStatement();
		break;
	case SETVAR:
		AssignStatement();
		break;
	case READ:
		cout<<"should add read();"<<endl;
		break;
	case STRING:
		ExecuteCmd();
		//m_token = getToken();
		break;
	default:
		if(m_token == ENDOFFILE)
			syntaxError("Parser Reach to End Of File Unexpected.");
		else
			syntaxError("Unexpected Token");
		printToken(m_token);
	}
}
void Parser::SequenceStatement()
{
	while( m_token != ELSE && m_token != FI &&
		m_token != ENDOFFILE && m_errorFlag != true)
	{
		Statement();
	}
}
void Parser::beginParser()
{
	m_token = getToken();
	SequenceStatement();
}
#ifdef	DEBUG_PARSER
int main()
{
	Parser p;
	p.beginParser();
	//cout<<g_variables.getVariable("int")<<endl;
	return 0;
}
#endif
