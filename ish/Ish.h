#ifndef	_ISH_H
#define	_ISH_H
#include<string>
using namespace std;
class	ish
{
public:
	ish();
	~ish();
	char *get_user()	const;
	void disp_cmd_prompt()	const;
private:
	void init_shell_environment();
	void init_cmd_prompt();
	char *m_user;
	char *m_path;
	char *m_pwd;
	char *m_hostname;
	string	m_cmd_prompt;
};
extern ish shell;
#endif	/*_ISH_H*/
