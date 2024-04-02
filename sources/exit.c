#include "../minishell.h"

void increase_shell_lvl(void)
{
	char	*shlvl_str;
	int		shlvl;
	shlvl_str = search_var_value("SHLVL");
	if(!shlvl_str)
		export(strdup("SHLVL=1"));
	else
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		shlvl_str = ft_itoa(shlvl);
		shlvl_str = ft_strjoin("SHLVL=", shlvl_str, 0, 1);
		export(shlvl_str);
	}
}

int run_exit(t_command *cmd, int cmd_n, b_tree *tree, int flag)
{
    if (flag)
    {
        free_char_pp(cmd[cmd_n].args);
	    free(cmd);
        destroy_tree(&tree);
		get_set_env(NULL,1);
        exit(0);
    }
    else 
    {
        exit(0);
    }
}