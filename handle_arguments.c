/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:07:05 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/04 19:14:51 by skawanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_arguments(int argc, char **argv, int *infile_fd, int *outfile_fd)
{
	if (argc != 5)
	{
		ft_putendl_fd("argc != 5", 2);
		exit(1);
	}
	*infile_fd = open(argv[1], O_RDONLY);
	if (*infile_fd < 0)
	{
		perror("can't open infile");
		exit (1);
	}
	*outfile_fd = open(argv[4], O_WRONLY);
	if (*outfile_fd < 0)
	{
		perror("can't open outfile");
		exit (1);
	}
}
