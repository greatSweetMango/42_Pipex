/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:00:53 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/09/05 18:00:54 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_allocate(void)
{
	ft_putstr_fd("pipex: allocate error!\n", STDERR);
	exit(1);
}

void	close_all_pipefd(int *fd, int error_case)
{
	close(fd[0]);
	close(fd[1]);
	if (error_case == 1)
		ft_putstr_fd("pipex: Here_doc allocate error!\n", STDERR);
	exit(error_case);
}

void	error_argument(void)
{
	ft_putstr_fd("pipex: Arguments is not enough!!\n", STDERR);
	exit(1);
}

void	error_excute_cmd(char *cmd)
{
	ft_putstr_fd("pipex: ", STDERR);
	ft_putstr_fd("can't excute commend!!(", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(")\n", STDERR);
	exit(1);
}
