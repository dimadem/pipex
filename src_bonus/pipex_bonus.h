/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:33:03 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 16:10:25 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "../external/ft_printf/src/ft_printf.h"

void	ft_process(char *argv, char **envp);
void	ft_result(int argc, char **argv, char **envp, int *fd);
void	ft_error(void);
void	ft_report(void);
char	*ft_find_path(char *cmd, char **envp);
void	ft_free_2d_arr(char **arr);
void	ft_free_3d_arr(char ***arr);
int		ft_open(char *argv, int flags);
void	ft_here_doc_process(int *outfile, int argc, char **argv);
void	ft_infile_process(int *infile, int *outfile, int argc, char **argv);
void	ft_execute(char *argv, char **envp);

#endif
