/*
 * Scanner.cc (C) Zhao Yanbai
 *
 * Wed Jul 9 09:53 CST 2008
 */
#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;
#include"Debug.h"
#include"Scanner.h"

//====================================================
//Static
//====================================================
ReservedWord Scanner::m_reservedWord[]=
{
	{"if",IF},	{"else",ELSE},	{"fi",FI},
	{"then",THEN},
	{"while",WHILE},{"do",DO},	{"done",DONE},
	{"read",READ},	{"[",LSB},	{"]",RSB},
	{"-eq",EQ},	{"-ne",NE},	{"-gt",GT},
	{"-ge",GE},	{"-lt",LT},	{"-le",LE},
};


Scanner::Scanner()
:m_source(stdin),m_currentLine(0),m_currentPos(0),m_bufferSize(0),
m_flagEOF(false),m_tokenStringIndex(0),m_state(START)
{
	/*m_source = fopen("/tmp/.ish_temp","w+");
	fclose(m_source);
	m_source = fopen("/tmp/.ish_temp","r");*/
}
Scanner::~Scanner()
{
}

char Scanner::getNextChar()
{
	if(m_currentPos < m_bufferSize)
		return m_buffer[m_currentPos++];
	
	//fflush(stdin);
	if(fgets(m_buffer, m_bufferCapacity-1, m_source))
	{
		int n = ftell(m_source);
		fseek(m_source,0,SEEK_END);
		fputc(EOF,m_source);
		fseek(m_source,n,SEEK_SET);
		m_bufferSize = strlen(m_buffer);
		m_currentPos = 0;
		m_currentLine++;
		return m_buffer[m_currentPos++];
	}
	else
	{
		m_flagEOF = true;
		return EOF;
	}
}
void Scanner::ungetNextChar()
{
	if(!m_flagEOF)
		if(m_currentPos > 0)		//Maybe Not Useful
			m_currentPos--;
}

TokenType Scanner::getToken()
{
	TokenType currentToken;
	bool save = false,doubleQuotation=false;
	char ch;
	char splitChar=' ';

	m_tokenStringIndex = 0;
	m_tokenString[0] = 0;

	while(m_state != AC)
	{
		ch = getNextChar();
		if(ch =='\"')
			m_state = STR;
		if(ch == EOF)
			return ENDOFFILE;

		switch(m_state)
		{
		case START:
			if(isWhite(ch))
			{
				save= false;
				m_state = START;
			}
			else if(ch == '#')
			{
				save=false;
				m_state = COMMENT;
			}
			else if(isIdent(ch))
			{
				save = true;
				m_state = IDENT;
			}
			else
			{
				switch(ch)
				{
				case '=':
					currentToken = ANS;
					m_state = STR;
					break;
				case '<':
					currentToken = RINS;
					m_state = FILEN;
					break;
				case '>':
					currentToken = ROUTS;
					m_state = FILEN;
					break;
				case '|':
					currentToken = PIPES;
					m_state = START;
					break;
				default:
					fprintf(stderr,"line: %d: Scanner can not recognize:%c\n",m_currentLine,ch);
					currentToken = ERROR;
					break;
				}
				return currentToken;
			}
			break;
		case IDENT:
			save = true;
			if(!isIdent(ch))
			{
				ungetNextChar();
				m_state = AC;
				save = false;
				currentToken = ID;
			}
			break;
		case COMMENT:
			while((ch != EOF) && (ch != '\n'))
				ch = getNextChar();
			if(ch == '\n')
				m_state = START;
			else if(ch == EOF)
			{
				m_state = AC;
				currentToken = ENDOFFILE;
			}
			break;
		case STR:
			save = false;
			while(true)
			{
				if(ch == EOF)
				{
					fprintf(stderr,"line: %d: unexpected EOF while looking for matching \"\n",m_currentLine);
					currentToken = ERROR;
					break;
				}
				if(ch == '\n' && !doubleQuotation)
					break;
				if(ch == ' ' && !doubleQuotation)
					break;

				if(ch == '\"' && !doubleQuotation)
					doubleQuotation = true;
				else if(ch == '\"' && doubleQuotation)
					doubleQuotation = false;
				else
				{
					m_tokenString[m_tokenStringIndex++]
					=ch;
					m_tokenString[m_tokenStringIndex]=0;
				}
				ch = getNextChar();
			}
			if(currentToken != ERROR)
				currentToken = STRING;
			m_state = AC;
			break;
		case FILEN:
			save = true;
			if(!isFilec(ch))
			{
				ungetNextChar();
				m_state = AC;
				save = false;
				currentToken = REDFN;
			}
			break;
		default:
			fprintf(stderr,"line: %d: Scanner Error...\n",m_currentLine);
			break;
		}
		if(save && (m_tokenStringIndex<m_tokenStringCapacity-1))
		{
			m_tokenString[m_tokenStringIndex++] = ch;
		}
		m_tokenString[m_tokenStringIndex] = 0;
	}
	if(currentToken == ID)
	{
		char cc = getNextChar();
		if(cc == '=')
			currentToken = SETVAR;
		else
			currentToken = lookupReservedWord(m_tokenString);
		ungetNextChar();
	}
	if(m_tokenString[0]=='$')
		currentToken = GETVAR;
	if(currentToken == ID)
	{/*
		bool dq = true;	//double quotation...
		for(int i=0; m_tokenString[i]; i++)
			if(m_tokenString[i] == '\"')
			{
				dq = (dq)false:true;
				for(int j=i+1;m_tokenString[j];j++)
					m_tokenString[j-1] = m_tokenString[j];
			}
		if(dq)*/
			currentToken = STRING;
		//else

		
	}
	
	m_state = START;
	return currentToken;
}
const char *Scanner::getTokenString() const
{
	return m_tokenString;
}

int Scanner::getCurrentLine() const
{
	return m_currentLine;
}

void Scanner::printToken(TokenType t) const
{
	switch(t)
	{
	case IF:	cout<<"if"<<endl;break;
	case ELSE:	cout<<"else"<<endl;break;
	case THEN:	cout<<"then"<<endl;break;
	case FI:	cout<<"fi"<<endl;break;
	case WHILE:	cout<<"while"<<endl;break;
	case DONE:	cout<<"done"<<endl;break;
	case READ:	cout<<"read"<<endl;break;
	case ENDOFFILE:	cout<<"EOF"<<endl;break;
	case ERROR:	cout<<"ERROR"<<endl;break;
	case REDFN:	cout<<"REDFN"<<endl;break;
	case RINS:	cout<<"RINS"<<endl;break;
	case ROUTS:	cout<<"ROUTS"<<endl;break;
	case PIPES:	cout<<"PIPES"<<endl;break;
	case ANS:	cout<<"ANS"<<endl;break;
	case LSB:	cout<<"LSB"<<endl;break;
	case RSB:	cout<<"RSB"<<endl;break;
	case SEMI:	cout<<"SEMI"<<endl;break;
	case ID:	cout<<"ID"<<endl;break;
	case DIGIT:	cout<<"DIGIT"<<endl;break;
	case STRING:	cout<<"STRING"<<endl;break;
	case SETVAR:	cout<<"SETVAR"<<endl;break;
	case GETVAR:	cout<<"GETVAR"<<endl;break;
	case EQ:	cout<<"EQ"<<endl;break;
	case NE:	cout<<"NE"<<endl;break;
	case GT:	cout<<"GT"<<endl;break;
	case GE:	cout<<"GE"<<endl;break;
	case LT:	cout<<"LT"<<endl;break;
	case LE:	cout<<"LE"<<endl;break;
	case DO:	cout<<"DO"<<endl;break;
	}
}

/*
bool Scanner::isDigit(const char &c)
{
	return ('0'<=c && c<='9');
}*/
bool Scanner::isIdent(const char &c)
{
	switch(c)
	{
	case '=':
	case '<':
	case '>':
	case ' ':
	case '|':
	case '\t':
	case '\n':
		return false;
		break;
	default:
		return true;
	//	break;
	}
}
bool Scanner::isAlpha(const char &c)
{
	return ( (c=='_') || ('a'<=c && c<='z') || ('A'<=c && c<='z'));
}
bool Scanner::isFilec(const char &c)
{
	return ( isAlpha(c) || c=='.' || c=='-');
}
bool Scanner::isWhite(const char &c)
{
	return ( c==' ' || c=='\t' || c=='\n');
}
TokenType Scanner::lookupReservedWord(const char *s)
{
	for(int i=0; i<m_maxReservedWordNum;i++)
	{
		if(strcmp(m_reservedWord[i].s,s) == 0)
			return m_reservedWord[i].t;
	}
	return ID;
}

int Scanner::getTokenStringLen() const
{
	//for safe...
	//then it will not overflow...
	//m_tokenString[m_tokenStringCapacity - 1] = 0;

	return strlen(m_tokenString);
}
void Scanner::setInputFile(const char *filepath)
{
	m_source = fopen(filepath,"r");
}

#ifdef	DEBUG_SCANNER
int main()
{
	cout<<"scanner"<<endl;
	Scanner s;
	TokenType t;

	//cout<<"test size:"<<sizeof(s)<<endl;
t = s.getToken();
while(t != ENDOFFILE)
{
	if(t == ERROR)
		return 1;
	cout<<s.getTokenString()<<":\t";
	s.printToken(t);	
	t = s.getToken();
}
	/*s.getNextChar();
	s.getNextChar();
	s.ungetNextChar();
	while(true)
		cout<<s.getNextChar();*/
	//while(true)
		/*cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;*/
		/*cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;
		cout<<s.getToken()<<endl;*/

	return 0;
}
#endif
