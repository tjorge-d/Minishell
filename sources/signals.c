#include "../minishell.h"

void    quit_here_doc(int signal)
{
	close(0);
	g_var = 130;
	(void)signal;
}

void    ctrl_c_signal_hd(int signal)
{
	g_var = 130;
	(void)signal;
}

void    ctrl_c_signal(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
	(void)signal;
}

