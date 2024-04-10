/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:33:03 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/04 17:35:16 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "../external/ft_printf/src/ft_printf.h"

typedef struct s_pipex
{
	char	**directories;
	int		shift;
	int		args_count;
	char	**args;
	char	***cmds;
	char	*infile;
	char	*outfile;

	int		pipe_fd[2];

	int		infile_fd;
	int		outfile_fd;

	int		here_doc;
}		t_pipex;

void	ft_init(t_pipex *pipex, int *argc, char **argv, char **envp);

char	**ft_parse_path(char **envp);
char	**ft_parse_args(t_pipex *pipex, char **argv);
char	***ft_set_cmds(t_pipex *pipex);
int		ft_open_file(t_pipex *pipex);
int		ft_create_pipes(t_pipex *pipex);

int		ft_processing(t_pipex *pipex);

void	ft_free_pipex(t_pipex *pipex);
void	ft_free_2d_arr(char **arr);
void	ft_free_3d_arr(char ***arr);

#endif
