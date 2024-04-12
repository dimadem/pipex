/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:55 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/11 13:26:05 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(void)
{
	perror ("Error");
	exit (EXIT_FAILURE);
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

void	ft_free_3d_arr(char ***arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		ft_free_2d_arr(arr[i]);
	free(arr);
}
