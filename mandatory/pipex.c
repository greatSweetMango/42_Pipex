/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyuki <jaehyuki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:06:20 by jaehyuki          #+#    #+#             */
/*   Updated: 2022/09/01 19:06:21 by jaehyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_here_doc(char *limiter, int fd[2])
{
	size_t	len_limiter;
	char	*line;
	int		status;

	len_limiter = ft_strlen(limiter);
	while (1)
	{
		status = get_next_line(STDIN, &line);
		if (status == 0)
			close_all_pipefd(fd, 0);
		else if (status == -1)
			close_all_pipefd(fd, 1);
		if (line[len_limiter] == '\n'
			&& limiter && !ft_strncmp(line, limiter, len_limiter))
			close_all_pipefd(fd, 0);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	*rv_cmd;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path = env[i] + 5;
	while (*path)
	{
		rv_cmd = ft_strjoin_free(ft_strjoin_free(ft_strndup(path,
						ft_strichr(path, ':')), "/"), cmd);
		if (!rv_cmd)
			return (NULL);
		if (access(rv_cmd, F_OK) == 0)
			return (rv_cmd);
		free(rv_cmd);
		if (ft_strichr(path, ':') >= 0)
			path += ft_strichr(path, ':') + 1;
		else
			path += ft_strlen(path);
	}
	return (cmd);
}

void	excute_cmd(char *cmd, char **env)
{
	char	**cmd_arr;
	char	*cmd_path;

	cmd_arr = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(cmd_arr[0], env);
	if (!cmd_path)
		error_allocate();
	execve(cmd_path, cmd_arr, env);
	error_excute_cmd(cmd_arr[0]);
}

void	redirection_excute(char *cmd, char **env, int d_flag)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	pid = fork();
	if (pid > 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		if (d_flag == HERE_DOC)
			read_here_doc(cmd, fd_pipe);
		else
		{
			close(fd_pipe[0]);
			dup2(fd_pipe[1], STDOUT);
			excute_cmd(cmd, env);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd_infile;
	int		fd_outfile;
	int		i;

	if (argc >= 5)
	{
		i = set_inout_fd(argv, argc, &fd_infile, &fd_outfile);
		dup2(fd_infile, STDIN);
		dup2(fd_outfile, STDOUT);
		if (i == 3)
			redirection_excute(argv[2], env, HERE_DOC);
		while (i < argc - 2)
		{
			redirection_excute(argv[i], env, 0);
			i++;
		}
		close(fd_infile);
		excute_cmd(argv[i], env);
	}
	else
		error_argument();
	exit(0);
}
