/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:07:05 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/06 22:12:47 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_arguments(int argc, char **argv, int *in_fd, int *out_fd)
{
	if (argc != 5)
	{
		ft_putendl_fd("argc != 5", 2);
		exit(1);
	}
	*in_fd = open(argv[1], O_RDONLY);
	if (*in_fd < 0)
	{
		ft_putstr_fd("pipex: no such file or directory :", 2);
		ft_putendl_fd(argv[1], 2);
	}
	*out_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*out_fd < 0)
	{
		perror("can't open outfile");
		exit (1);
	}
}
