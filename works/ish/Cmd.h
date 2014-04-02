#ifndef	_CMD_H
#define	_CMD_H
#include<stdio.h>
#include<stdlib.h>
#define	CMD_BUF_SIZE	255
typedef int ExitCode;
class	cmd
{
public:
	cmd();
	~cmd();
	char	*get_cmd(FILE *fp=stdin);
	void	disp_cmd() const;
	int	makeargv(const char *cmd_buf,char ***argv,const char *delimiters=m_delimiters);
	void	freemakeargv(char **argv);
	ExitCode ExecuteCommand(char **argv);
private:
	char	*m_cmd_buf;
	int	m_buf_pos;
	const int	m_buf_size;
	static const char	*m_delimiters;
};
#endif	/*_CMD_H*/
