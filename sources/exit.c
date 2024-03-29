#include "../minishell.h"

int run_exit(t_command *cmd, int cmd_n, b_tree *tree, int flag)
{
    if (flag)
    {
        free_char_pp(cmd[cmd_n].args);
	    free(cmd);
        destroy_tree(&tree);
        exit(0);
    }
    else 
    {
        exit(0);
    }
}