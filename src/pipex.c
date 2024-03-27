#include "pipex.h"

int pipex(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (argc != 5)
    {
        perror("Error: Invalid number of arguments\n");
        return (-1);
    }
    if (ft_init(&pipex, argc, argv, envp) == -1)
        return (-1);
    if (ft_create_pipes(&pipex) == -1)
        return (-1);
    if (ft_fork(&pipex) == -1)
        return (-1);
    ft_free(&pipex);
    return (0);
}
