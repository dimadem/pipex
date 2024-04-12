/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:37:34 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 18:14:54 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute(char *argv, char **envp);
int		ft_c_get_next_line(char **line);

void	ft_here_doc_process(int *outfile, int argc, char **argv)
{
	pid_t	reader;
	int		fd[2];
	char	*temp_data;
	char	*line;

	if (argc < 6)
		ft_report();
	*outfile = ft_open(argv[argc - 1], 0);
	pipe(fd);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		line = ft_get_next_line(STDIN_FILENO);
		while (line)
		{
			ft_printf("temp_data -> %s\n", *temp_data);
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			line = ft_get_next_line(STDIN_FILENO);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	ft_infile_process(int *infile, int *outfile, int argc, char **argv)
{
	*infile = ft_open(argv[1], 1);
	*outfile = ft_open(argv[argc - 1], 2);
	if (dup2(*infile, STDIN_FILENO) == -1)
		ft_error();
}

void	ft_process(char *argv, char **envp)
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
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	ft_c_get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		status;
	char	c;

	i = 0;
	status = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	status = read(0, &c, 1);
	while (status && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		status = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	ft_printf("line -> %s\n", *line);
	free(buffer);
	return (status);
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
