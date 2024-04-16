/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:37:34 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/11 14:07:25 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *argv, char **envp);

void	ft_process(char **argv, char **envp, int	*fd)
{
	int		infile;

	infile = open(argv[1], O_RDONLY, 644);
	if (infile == -1)
		ft_error();
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_execute(argv[2], envp);
}

void	ft_result(int argc, char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	ft_execute(argv[3], envp);
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
