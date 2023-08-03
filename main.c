/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:25:46 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/04 01:32:57 by skawanis         ###   ########.fr       */
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
	size_t	path_len;
	pid_t	pid;

	new_cmd = ft_split(cmd, ' ');
	path = get_path(envp, &path_len);
	binary_path = search_binary(path, path_len, new_cmd[0]);
	printf("dupin -> %d\n", dup2(in_fd, 0));
	printf("dupout -> %d\n", dup2(out_fd, 1));
	pid = fork();
	if (pid > 0)
	{
		puts("hello from parente prosess and waiting...");
		wait(NULL);
		puts("hello from parent prosess");
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
	printf("infd:%d\noutfd:%d\n", infile_fd, outfile_fd);
	execute_cmd(argv[2], envp, infile_fd, my_pipe[PIPE_WRITE]);
	execute_cmd(argv[3], envp, my_pipe[PIPE_READ], outfile_fd);
}
