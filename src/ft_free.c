#include "pipex.h"

void ft_free(t_pipex *pipex)
{
    if (pipex->cmd)
        ft_free_cmd(pipex->cmd);
    if (pipex->infile)
        free(pipex->infile);
    if (pipex->outfile)
        free(pipex->outfile);
}
