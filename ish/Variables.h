/*
 * Variables.h (C) Zhao Yanbai
 *
 * Wed Jul 9 00:33 CST 2008
 *
 */

#ifndef	_VARIABLES_H
#define	_VARIABLES_H
#include"BinaryTree.h"
class Variables
{
public:
	Variables();
	~Variables();
	bool storeVariable(const char *variable, const char *value);
	bool deleteVariable(const char *variable);
	const char *getVariable(const char *variable) const;

private:
	BinaryTree m_variables;
	BinaryTree m_exports;
};

extern Variables g_variables;

#endif	//_VARIABLES_H
