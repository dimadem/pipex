/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:55 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 20:21:35 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 777);
	else if (i == 1)
		file = open(argv, O_RDONLY, 777);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 777);
	if (file == -1)
		ft_error();
	return (file);
}

char	*ft_find_path(char *cmd, char **envp)
{
	char	**directories;
	char	*temp_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		++i;
	directories = ft_split(envp[i] + 5, ':');
	i = -1;
	while (directories[++i] != NULL)
	{
		temp_path = ft_strjoin(directories[i], "/");
		path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	ft_free_2d_arr(directories);
	return (NULL);
}

void	ft_free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}

void	ft_report(void)
{
	errno = EINVAL;
	perror("Error");
	ft_printf("./pipex <infile> <cmd1> <cmd2> <...> <outfile>\n");
	ft_printf("./pipex_bonus here_doc LIMITER <cmd> <cmd1> <...> <outfile>\n");
	exit(EXIT_SUCCESS);
}

void	ft_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
