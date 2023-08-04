/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skawanis <skawanis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:07:05 by skawanis          #+#    #+#             */
/*   Updated: 2023/08/04 18:05:54 by skawanis         ###   ########.fr       */
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
	*outfile_fd = open(argv[4], O_WRONLY);
}
