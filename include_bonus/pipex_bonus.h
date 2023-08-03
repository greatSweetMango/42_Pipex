/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:05:49 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/09/01 19:05:53 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

# define INFILE 0
# define OUTFILE 1
# define HERE_DOC 2
# define STDIN 0
# define STDOUT 1
# define STDERR 2

int		set_inout_fd(char **argv, int argc, int *fd_infile, int *fd_outfile);
void	close_all_pipefd(int *fd, int error_case);
void	error_argument(void);
void	error_excute_cmd(char *cmd);
void	error_allocate(void);

#endif
