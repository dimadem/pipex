#include "pipex.h"
#include <cstddef>

int ft_init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
    pipex->cmd = NULL;
    pipex->infile = NULL;
    pipex->outfile = NULL;
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