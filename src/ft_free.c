#include "pipex.h"

void ft_free_pipex(t_pipex *pipex)
{
    if (pipex->directories)
        ft_free_2d_arr(pipex->directories);
    if (pipex->args)
        ft_free_2d_arr(pipex->args);
    if (pipex->cmds)
        ft_free_3d_arr(pipex->cmds);
    if (pipex->infile)
        free(pipex->infile);
    if (pipex->outfile)
        free(pipex->outfile);
}

void ft_free_2d_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_free_3d_arr(char ***arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        ft_free_2d_arr(arr[i]);
        i++;
    }
    free(arr);
}