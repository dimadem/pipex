#include "pipex.h"

char **ft_parse_args(t_pipex *pipex, char **argv)
{
    static char **args;
    static int i;
    args = (char **)malloc(sizeof(char **) * (pipex->args_count + 1));
    if (!args)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < pipex->args_count)
    {
        ft_printf("argv[%d] -> %s\n", (i + pipex->shift), argv[i + pipex->shift]);
        args[i] = ft_strdup(argv[i + pipex->shift]);
        if (!args[i])
        {
            ft_free_2d_arr(args);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    args[i] = NULL;
    ft_printf("\n");
    ft_printf("args[0]: %s\nargs[1]: %s\nargs[2]: %s\nargs[3]: %s\n\n", args[0], args[1], args[2], args[3]);
    return (args);
}

char **ft_parse_path(char **envp)
{
    static char *path = NULL;
    static char **directories = NULL;
    static int i;

    i = -1;
    while (*envp[++i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path = ft_strdup(envp[i] + 5);
            if (!path)
                exit(EXIT_FAILURE);
            break;
        }
    }
    directories = ft_split(path, ':');
    free(path);
    return (directories);
}

int ft_open_file(t_pipex *pipex)
{
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    if (pipex->infile_fd == -1)
    {
        ft_printf("Error: Failed to open infile\n");
        exit(EXIT_FAILURE);
    }
    pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile_fd == -1)
    {
        ft_printf(" Error: Failed to open outfile\n");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int ft_create_pipes(t_pipex *pipex)
{
    if (pipe(pipex->pipe_fd) == -1)
    {
        ft_printf("Error: Failed to create pipe\n");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
