#include "pipex.h"

int ft_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
    pipex->cmd = ((void *)0);
    pipex->infile = ((void *)0);
    pipex->outfile = ((void *)0);
    pipex->infile_fd = -1;
    pipex->outfile_fd = -1;
    pipex->pipe_fd[0] = -1;
    pipex->pipe_fd[1] = -1;
    if (ft_parse_pipex(pipex, argc, argv) == -1)
        return (-1);
    if (ft_open_files(pipex) == -1)
        return (-1);
    if (ft_parse_cmd(pipex, envp) == -1)
        return (-1);
    return (0);
}
