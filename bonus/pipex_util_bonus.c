/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:43:35 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/09/04 19:43:36 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file, int open_case)
{
	int	fd;

	if (open_case == INFILE)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(file, STDERR);
			ft_putstr_fd("pipex: is not exist!\n", STDERR);
			exit(1);
		}
	}
	else if (open_case == OUTFILE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		ft_putstr_fd("can't open WRITE_FILE!!\n", STDERR);
	return (fd);
}

int	set_inout_fd(char **argv, int argc, int *fd_infile, int *fd_outfile)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		*fd_infile = STDIN;
		*fd_outfile = open_file(argv[argc - 1], HERE_DOC);
		return (3);
	}
	else
	{
		*fd_infile = open_file(argv[1], INFILE);
		*fd_outfile = open_file(argv[argc - 1], OUTFILE);
		return (2);
	}
}
