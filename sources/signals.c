#include "../minishell.h"

void    quit_signal(int signal)
{
	char str[2];

	str[0] = -1;
	str[1] = '\0';
	write(0, str, 2);
	global_var = signal;
	(void) signal;
}

void    ctrl_c_signal(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global_var = signal;

}

void	sigint_handler_nonl(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}