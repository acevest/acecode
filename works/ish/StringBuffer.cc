/*
 * StringBuffer.cc (C) Zhao Yanbai
 *
 * Tue Jul 15 14:12 CST 2008
 */
#include"Debug.h"
#include"StringBuffer.h"
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

StringBuffer::StringBuffer():m_string(NULL),m_length(0),m_size(0)
{
}


StringBuffer::~StringBuffer()
{
//	m_length = 0;
//	m_size = 0;
	if(m_string != NULL)
		free(m_string);
}

bool StringBuffer::setString(const char *s)
{
	int len = strlen(s);
	if(len +1 > m_size)
	{
		int size = (len + 1)*2 +100;
		char *p = (char *) realloc(m_string, size);
		if(p == NULL)
			return false;
		m_string = p;
		m_size = size;
	}
	strcpy(m_string, s);
	m_length = len;
	return true;
}

bool StringBuffer::appendString(const char *s)
{
	int len = strlen(s);
	if(m_length + len + 1 > m_size)
	{
		int size = (m_length + len +1)*2 + 100;
		char *p = (char *) realloc(m_string, size);
		if(p == NULL)
			return false;
		m_string = p;
		m_size = size;
	}
	strcpy(m_string+m_length, s);
	m_length += len;
	return true;
}
const char *StringBuffer::getString() const
{
	return m_string;
}

/*
#ifdef	DEBUG_STRINGBUFFER
int main()
{
	StringBuffer sb;
	sb.appendString("AA");
	//sb.setString("A");
	sb.appendString("AAA");
	cout<<sb.getString()<<endl;
}
#endif*/
