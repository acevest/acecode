/*
 * Variables.cc (C) Zhao Yanbai
 *
 * Wed Jul 9 00:38 CST 2008
 *
 */
#include"Variables.h"
#include"Debug.h"
#include<iostream>
using namespace std;

Variables::Variables()
{
#ifdef	DEBUG_VARIABLES
	cout<<"Variables"<<endl;
#endif
}
Variables::~Variables()
{
#ifdef	DEBUG_VARIABLES
	cout<<"~Variables"<<endl;
#endif
}

bool Variables::storeVariable(const char *variable, const char *value)
{
	m_variables.deleteNode(variable);
	return m_variables.insertNode(variable, value);
}
bool Variables::deleteVariable(const char *variable)
{
	return m_variables.deleteNode(variable);
}
const char *Variables::getVariable(const char *variable) const
{
	return m_variables.getNode(variable);
}

Variables g_variables;

#ifdef	DEBUG_VARIABLES
int main()
{
	Variables v;

	v.deleteVariable("VD");
	v.storeVariable("VA","VAAAA");
	v.storeVariable("VB","VBBBB");
	v.storeVariable("VC","VCCCC");
	v.storeVariable("VD","VDDDD");
	v.deleteVariable("VA");
	v.deleteVariable("VB");
	v.deleteVariable("VC");
	//cout<<v.getVariable("VB")<<endl;
	cout<<v.getVariable("VD")<<endl;
	v.deleteVariable("VD");
	v.deleteVariable("VD");
	cout<<v.getVariable("VD")<<endl;
	//v.deleteVariable("VC");
	return 0;
}
#endif//DEBUG_VARIABLES
