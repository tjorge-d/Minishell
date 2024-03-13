#include "../minishell.h"


char *get_error_msg_cd(char *arg)
{
	return(ft_strjoin("Error: cd: ", arg, 0, 0));
}

void	ft_chdir_our_env(char *new_dir)
{
	char **env;

	env = get_set_env(NULL, 0);
	export (ft_strjoin("OLDPWD=", search_var_value("PWD"),0,0));
	export (ft_strjoin("PWD=", new_dir,0,0));
}

void	cd_without_args()
{
	char	*error_msg;
	char	*home_value;
	char	*cwd;	

	home_value = search_var_value("HOME");
	printf("HOME WAS%s\n", home_value);
	if (chdir(home_value))
	{
		error_msg = get_error_msg_cd(home_value);
		ft_putstr_fd(error_msg, 2);
		perror(NULL);
		return;
	}
	cwd = getcwd(NULL, 0);
	ft_chdir_our_env(cwd);
	free(cwd);
}

void	cd_with_arg(char *arg)
{
	char	*error_msg;
	char	*cwd;

	if (ft_strncmp("-", arg, 2))
	{
		cd_with_arg(search_var_value("OLDPWD"));
	}
	if (chdir(arg))
	{
		error_msg = get_error_msg_cd(arg);
		ft_putstr_fd(error_msg, 2);
		perror(NULL);
		return ;
	}
	cwd = getcwd(NULL, 0);
	ft_chdir_our_env(cwd);
	free(cwd);
}
