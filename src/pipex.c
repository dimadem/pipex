/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:48:31 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 20:21:55 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_process(argv, envp, fd);
		waitpid(pid, NULL, 0);
		ft_result(argc, argv, envp, fd);
	}
	else
	{
		errno = EINVAL;
		perror("Error");
		ft_printf("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
