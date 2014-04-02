/*
 * StringBuffer.h (C) Zhao Yanbai
 *
 * Tue Jul 15 14:11 CST 2008
 */
#ifndef	_STRINGBUFFER_H
#define _STRINGBUFFER_H

#include<iostream>
using namespace std;

class StringBuffer
{
public:
	StringBuffer();
	~StringBuffer();
	bool appendString(const char *s);
	bool setString(const char *s);
	const char *getString() const;
private:
	char *m_string;
	int m_length,m_size;
};

#endif	//_STRINGBUFFER_H
