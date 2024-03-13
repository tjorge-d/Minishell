#include "../minishell.h"

int main(int argc, char ** argv, char **envp)
{
	char **env;	
	char *exportable;

	exportable = ft_strdup("PWD=AFRICA");
	env = NULL;
	printf("%p\n", &env);
	env  = copy_array(envp);
	get_set_env(&env, 0);
	print_array(get_set_env(NULL,0));
	cd_without_args();
	free_char_pp(env);
	get_set_env(NULL, 1);
	(void) argc;
	(void) argv;
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
}