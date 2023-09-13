/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:50:35 by skawanis          #+#    #+#             */
/*   Updated: 2023/09/14 01:10:23 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	size_t	i;
	char	**path;

	i = 0;
	while (1)
	{
		if (envp[i] == NULL)
			break ;
		if (start_with(envp[i], "PATH="))
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (path);
}

char	*search_binary(char **path, char *cmd_name)
{
	size_t	i;
	char	*cmd_path;
	char	*new_cmd;

	new_cmd = ft_strjoin("/", cmd_name);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], new_cmd);
		free((void *)path[i]);
		path[i] = NULL;
		if (access(cmd_path, X_OK) == 0)
		{
			free_all((void *)path, i + 1);
			ft_free2(path, new_cmd);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free2(path, new_cmd);
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putendl_fd(cmd_name, 2);
	return (NULL);
}
