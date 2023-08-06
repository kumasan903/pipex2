/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:25:46 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/06 21:54:13 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PIPE_READ 0
#define PIPE_WRITE 1

void	execute_cmd(char *cmd, char **envp, int in_fd, int out_fd)
{
	char	**new_cmd;
	char	**path;
	char	*binary_path;
	pid_t	pid;

	new_cmd = ft_split(cmd, ' ');
	path = get_path(envp);
	binary_path = search_binary(path, new_cmd[0]);
	dup2(in_fd, 0);
	close(in_fd);
	dup2(out_fd, 1);
	close(out_fd);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		free(binary_path);
		free_all((void **)new_cmd, 0);
	}
	if (pid == 0)
	{
		if (execve(binary_path, new_cmd, envp))
			perror("pipex");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	infile_fd;
	int	outfile_fd;
	int	my_pipe[2];

	if (pipe(my_pipe))
		exit (1);
	handle_arguments(argc, argv, &infile_fd, &outfile_fd);
	if (infile_fd >= 0)
		execute_cmd(argv[2], envp, infile_fd, my_pipe[PIPE_WRITE]);
	else
		close(my_pipe[PIPE_WRITE]);
	execute_cmd(argv[3], envp, my_pipe[PIPE_READ], outfile_fd);
	return (0);
}
