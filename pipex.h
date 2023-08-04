/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:25:51 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/04 19:35:53 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

void	execute_cmd(char *cmd, char **envp, int in_fd, int out_fd);
void	handle_arguments(int argc, char **argv, int *in_fd, int *out_fd);
char	**get_path(char **envp);
char	*search_binary(char **path, char *cmd_name);
int		start_with(char *heystack, char *needle);
char	*ft_strndup(const char *s1, size_t size);

#endif
