/*
 * Scanner.h (C) Zhao Yanbai
 *
 * Wed Jul 9 09:45 CST 2008
 */
#ifndef	_SCANNER_H
#define	_SCANNER_H
#include<iostream>
using namespace std;

typedef	enum tokentype
{
	IF,ELSE,THEN,FI,WHILE,DO,DONE,READ,	//control tokenType...
	ENDOFFILE,ERROR,
	REDFN,
	RINS,ROUTS,PIPES,ANS,LSB,RSB,SEMI,
	//REDF: Redirect File Name
	//RINS: Redirect In Sign
	//PIPES: Pipe Sign
	//ANS: Assign Sign
	//LSB: Left Square Bracket
	ID,DIGIT,STRING,SETVAR,GETVAR,
	EQ,NE,GT,GE,LT,LE
} TokenType;

typedef	enum state
{
	START,IDENT,COMMENT,ASSIGN,STR,PIPE,FILEN,
	AC,STATE_ERROR
} State;

typedef struct rw
{
	const char *s;
	TokenType t;
}ReservedWord,*pReservedWord;


class Scanner
{
public:
	Scanner();
	~Scanner();
	char getNextChar();
	void ungetNextChar();
	TokenType getToken();
	const char *getTokenString() const;
	int getCurrentLine() const;
	void printToken(TokenType t) const;
	int getTokenStringLen() const;
	void setInputFile(const char *filepath);


	//static bool isDigit(const char &c);
	static bool isIdent(const char &c);
	static bool isAlpha(const char &c);
	static bool isFilec(const char &c);
	static bool isWhite(const char &c);
	static TokenType lookupReservedWord(const char *s);
private:
	FILE *m_source;
	//istream m_source;
	bool m_flagEOF;
	State m_state;

	static const int m_bufferCapacity = 256;
	static const int m_tokenStringCapacity = 256;
	static const int m_maxReservedWordNum = 16;
	char m_buffer[m_bufferCapacity];
	char m_tokenString[m_tokenStringCapacity];
	int m_currentLine,m_currentPos,m_bufferSize;
	int m_tokenStringIndex;
	static ReservedWord m_reservedWord[];
};

#endif/*_SCANNER_H*/
