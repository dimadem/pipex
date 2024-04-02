#include "pipex.h"

void ft_free_pipex(t_pipex *pipex)
{
    if (pipex->directories)
        ft_free_2d_arr(pipex->directories);
    if (pipex->args)
        ft_free_2d_arr(pipex->args);
    if (pipex->cmds)
        ft_free_3d_arr(pipex->cmds);
}

void ft_free_2d_arr(char **arr)
{
    int i;

    i = -1;
    while (arr[++i] != NULL)
        free(arr[i]);
    free(arr);
}

void ft_free_3d_arr(char ***arr)
{
    int i;

    i = -1;
    while (arr[++i] != NULL)
        ft_free_2d_arr(arr[i]);
    free(arr);
}