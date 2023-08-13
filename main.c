/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:25:46 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/13 19:24:47 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PIPE_READ 0
#define PIPE_WRITE 1

pid_t	execute_cmd(char *cmd, char **envp, int in_fd, int out_fd)
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
		free(binary_path);
		free_all((void **)new_cmd, 0);
		return(pid);
	}
	if (pid == 0)
	{
		if (execve(binary_path, new_cmd, envp))
			perror("pipex");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile_fd;
	int	outfile_fd;
	int	my_pipe[2];
	pid_t	pid[2];

	if (pipe(my_pipe))
		exit (1);
	handle_arguments(argc, argv, &infile_fd, &outfile_fd);
	if (infile_fd >= 0)
		pid[0] = execute_cmd(argv[2], envp, infile_fd, my_pipe[PIPE_WRITE]);
	else
		close(my_pipe[PIPE_WRITE]);
	pid[1] = execute_cmd(argv[3], envp, my_pipe[PIPE_READ], outfile_fd);
	waitpid(pid[0], NULL, WNOHANG);
	waitpid(pid[1], NULL, WNOHANG);
	return (0);
}
