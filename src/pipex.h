/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:33:03 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/11 14:02:38 by dmdemirk         ###   ########.fr       */
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

void	ft_process(char **argv, char **envp, int *fd);
void	ft_result(int argc, char **argv, char **envp, int *fd);
void	ft_error(void);
char	*ft_find_path(char *cmd, char **envp);
void	ft_free_2d_arr(char **arr);
void	ft_free_3d_arr(char ***arr);

#endif
