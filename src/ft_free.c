#include "pipex.h"

void ft_free(t_pipex *pipex)
{
    if (pipex->cmds)
        ft_free_arr(pipex->cmds);
    if (pipex->infile)
        free(pipex->infile);
    if (pipex->outfile)
        free(pipex->outfile);
}
