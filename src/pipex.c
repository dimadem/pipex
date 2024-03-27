#include "pipex.h"

int pipex(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc != 5)
        return (ft_error("Error: Invalid number of arguments\n"));
    if (ft_init_pipex(&pipex, argc, argv, envp) == -1)
        return (-1);
    if (ft_create_pipes(&pipex) == -1)
        return (-1);
    if (ft_fork_pipex(&pipex) == -1)
        return (-1);
    ft_free_pipex(&pipex);
    return (0);
}