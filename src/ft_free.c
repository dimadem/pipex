#include "pipex.h"

void ft_free_pipex(t_pipex *pipex)
{
    if (pipex->cmd)
        ft_free_cmd(pipex->cmd);
    if (pipex->infile)
        free(pipex->infile);
    if (pipex->outfile)
        free(pipex->outfile);
}