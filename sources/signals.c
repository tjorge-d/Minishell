#include "../minishell.h"

void    quit_signal(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_redisplay();
}
void    exit_signal(int signal)
{
	(void)	signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}