/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:48:31 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/04 17:49:56 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	// ft_printf("\nINPUT:\n");
	// ft_printf("amount\n");
	// ft_printf("argc: %d\n", argc);
	// ft_printf("\nARGUMENTS\n");
	// ft_printf("argv[0]: %s\nargv[1]: %s\nargv[2]: %s\nargv[3]: %s\nargv[4]: %s\nargv[5]: %s\nargv[6]: %s\nargv[7]: %s\n\n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
	// printf("envp: %s %s %s %s\n", envp[1], envp[2], envp[3], envp[4]);
	if (argc < 5)
	{
		errno = EINVAL;
		perror("Error: not enough arguments");
		return (EXIT_FAILURE);
	}
	// ft_printf("\n**ft_init**\n");
	ft_init(&pipex, &argc, argv, envp);
	// ft_printf("\n**ft_processing**\n");
	ft_processing(&pipex);
	ft_free_pipex(&pipex);
	return (EXIT_SUCCESS);
}
