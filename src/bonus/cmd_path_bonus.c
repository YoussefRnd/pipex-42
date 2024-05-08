/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:55:03 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 11:00:46 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	free_double_char_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*find_env_path(char **env_vars)
{
	int	index;

	index = 0;
	while (env_vars[index] != NULL)
	{
		if (ft_strnstr(env_vars[index], "PATH=", 5))
			return (env_vars[index] + 5);
		index++;
	}
	return (NULL);
}

char	*is_path_valid(char *cmd, char **env_vars)
{
	char	*env_path;
	char	**path_dirs;
	char	*cmd_path;
	int		i;
	char	*cmd_slash;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	env_path = find_env_path(env_vars);
	path_dirs = ft_split(env_path, ':');
	cmd_path = NULL;
	i = 0;
	while (path_dirs[i])
	{
		cmd_slash = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(path_dirs[i], cmd_slash);
		free(cmd_slash);
		if (!access(cmd_path, X_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_double_char_ptr(path_dirs);
	return (cmd_path);
}
