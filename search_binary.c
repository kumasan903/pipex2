/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:50:35 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/04 19:19:09 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char**envp, size_t *path_len)
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
	*path_len = 0;
	while (path[*path_len] != NULL)
		*path_len += 1;
	return (path);
}

char	*search_binary(char **path, size_t path_len, char *cmd_name)
{
	size_t	i;
	char	**cmd_path_list;
	char	*new_cmd;

	new_cmd = ft_strjoin("/", cmd_name);
	cmd_path_list = ft_calloc(sizeof(char *), path_len + 1);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path_list[i] = ft_strjoin(path[i], new_cmd);
		free((void *)path[i]);
		path[i] = NULL;
		if (access(cmd_path_list[i], X_OK) == 0)
			return ((char *)cmd_path_list[i]);
		i++;
	}
	free(path);
	return (cmd_name);
}
