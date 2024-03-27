#include "pipex.h"

int ft_create_pipes(t_pipex *pipex)
{
    if (pipe(pipex->pipe_fd) == -1)
        perror(" Error: Failed to create pipe\n");
    return (0);
}

int ft_parse_cmd(t_pipex *pipex, char **envp)
{
    char *path = ((void *)0);
    char *cmd;
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path = ft_strdup(envp[i] + 5);
            break;
        }
        i++;
    }
    if (!path)
        return (-1);
    cmd = ft_strjoin("/", pipex->cmd[0]);
    pipex->cmd[0] = ft_strjoin(path, cmd);
    free(path);
    free(cmd);
    return (0);
}

int ft_open_files(t_pipex *pipex)
{
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    if (pipex->infile_fd == -1)
    {
        perror(" Error: Failed to open infile\n");
        return (-1);
    }
    pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile_fd == -1)
    {
        perror(" Error: Failed to open outfile\n");
        return (-1);
    }
    return (0);
}

void ft_free_cmd(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}

int ft_parse_pipex(t_pipex *pipex, int argc, char **argv)
{
    int i;

    i = 0;
    while (i < argc)
    {
        if (ft_strncmp(argv[i], "-i", 3) == 0)
            pipex->infile = ft_strdup(argv[i + 1]);
        if (ft_strncmp(argv[i], "-o", 3) == 0)
            pipex->outfile = ft_strdup(argv[i + 1]);
        i++;
    }
    if (!pipex->infile || !pipex->outfile)
        return (-1);
    pipex->cmd = ft_split(argv[3], ' ');
    return (0);
}