#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    ft_printf("argc: %d\n", argc);
    ft_printf("argv: %s %s %s %s\n\n", argv[1], argv[2], argv[3], argv[4]);
    // printf("envp: %s %s %s %s\n", envp[1], envp[2], envp[3], envp[4]);
    if (argc < 5)
    {
        errno = EINVAL;
        perror("Error: not enough arguments");
        return (EXIT_FAILURE);
    }
    ft_init(&pipex, &argc, argv, envp);
    ft_processing(&pipex);
    return (EXIT_SUCCESS);
}