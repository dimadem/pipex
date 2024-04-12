/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:48:31 by dmdemirk          #+#    #+#             */
/*   Updated: 2024/04/12 16:52:54 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	shift;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			shift = 3;
			ft_printf("");
			ft_here_doc_process(&outfile, argc, argv);
		}
		else
		{
			shift = 2;
			ft_infile_process(&infile, &outfile, argc, argv);
		}
		while (shift < argc - 2)
			ft_process(argv[++shift], envp);
		dup2(outfile, STDOUT_FILENO);
		ft_execute(argv[argc - 2], envp);
	}
	else
		ft_report();
	return (EXIT_SUCCESS);
}
