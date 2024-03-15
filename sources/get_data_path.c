#include "../minishell.h"

int	is_built_in(char *line)
{
	if (!ft_strncmp(line, "echo", 6) \
		|| !ft_strncmp(line, "cd", 3) \
		|| !ft_strncmp(line, "pwd", 4) \
		|| !ft_strncmp(line, "export", 8) \
		|| !ft_strncmp(line, "unset", 7) \
		|| !ft_strncmp(line, "env", 4) \
		|| !ft_strncmp(line, "exit", 6))
		return (1);
	return (0);
}

char	*check_command(char **path, char* data)
{
	int		i;
	char	*new_data;

	i = -1;
	while (path[++i])
	{
		new_data = ft_strjoin(path[i], "/", 0 , 0);
		if (new_data == NULL)
			return (free(data), NULL);
		new_data = ft_strjoin(new_data, data, 1 , 0);
		if (new_data == NULL)
			return (free(data), NULL);
		if (access(new_data, X_OK) == 0)
		{
			free(data);
			return (new_data);
		}
		else
			free(new_data);
	}
	return (data);
}

char	*get_data_path(char *data)
{
	char	**paths;
	char	*path;

	if (is_built_in(data))
		return (data);
	path = search_var_value("PATH");
	if (!path)
		return (data);
	paths = ft_split(path, ':');
	if (!paths)
		return (data);
	data = check_command(paths, data);
	return (data);
}