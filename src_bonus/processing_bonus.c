/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:37:34 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 21:05:26 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute(char *argv, char **envp);
int		ft_c_get_next_line(char **line);
void	ft_moving_lines(int *fd, char **argv);

void	ft_here_doc_process(int *outfile, int argc, char **argv)
{
	pid_t		reader;
	int			fd[2];

	if (argc < 6)
		ft_report();
	*outfile = ft_open(argv[argc - 1], 0);
	pipe(fd);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		ft_moving_lines(fd, argv);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	ft_moving_lines(int *fd, char **argv)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit (EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
	}
	free(line);
}

void	ft_infile_process(int *infile, int *outfile, int argc, char **argv)
{
	*infile = ft_open(argv[1], 1);
	*outfile = ft_open(argv[argc - 1], 2);
	if (dup2(*infile, STDIN_FILENO) == -1)
		ft_error();
}

void	ft_child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error();
		close(fd[1]);
		ft_execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error();
		waitpid(pid, NULL, 0);
	}
}

void	ft_execute(char *argv, char **envp)
{
	char	*path;
	char	**cmds;
	int		i;

	i = -1;
	cmds = ft_split(argv, ' ');
	path = ft_find_path(cmds[0], envp);
	if (!path)
	{
		ft_free_2d_arr(cmds);
		ft_error();
	}
	if (execve(path, cmds, envp) == -1)
		ft_error();
}
