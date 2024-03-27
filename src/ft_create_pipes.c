#include "pipex.h"

int ft_create_pipes(t_pipex *pipex)
{
    if (pipe(pipex->pipe_fd) == -1)
        perror(" Error: Failed to create pipe\n");
    return (0);
}