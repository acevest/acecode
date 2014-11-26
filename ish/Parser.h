/*
 * Parser.h (C) Zhao Yanbai
 *
 * Sat Jul 12 16:50 2008
 */
#ifndef	_PARSER_H
#define	_PARSER_H

#include"Scanner.h"
#include"Variables.h"
#include"StringBuffer.h"
#include"Cmd.h"
typedef int ExitCode;

class Parser:public Scanner
{
public:
	Parser();
	~Parser();
	void beginParser();
	//TokenType getToken();
	//int getCurrentLine() const;
	void syntaxError(const char *s);
	void match(TokenType e);

	bool isControlCmd() const;

	void Statement();
	void SequenceStatement();
	void IfStatement();
	void WhileStatement();
	void AssignStatement();
	ExitCode ExecuteCmd();
	ExitCode Exp();
private:
	TokenType m_token,m_lastToken;
	//Scanner m_scanner;
	bool m_errorFlag;
};

extern StringBuffer g_redirectFile;
extern bool g_redirectInFlag;
extern bool g_redirectOutFlag;
extern cmd  g_command;
#endif//_PARSER_H
