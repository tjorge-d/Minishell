#include "../minishell.h"

void    quit_signal(int signal)
{
	rl_on_new_line();
	rl_replace_line("BOAS", 0);
	global_var = signal;
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