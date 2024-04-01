#include "pipex.h"

char **ft_parse_args(t_pipex *pipex, char **argv)
{
    char **args;
    int i;
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
    char *path = NULL;
    char **directories = NULL;
    int i;

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

char ***ft_set_cmds(t_pipex *pipex)
{
    char ***cmds;
    int i, j;

    i = 0;
    j = 0;
    cmds = (char ***)malloc(sizeof(char **) * ((pipex->args_count / 2) + 1));
    if (!cmds)
        exit(EXIT_FAILURE);
    while (i < pipex->args_count)
    {
        cmds[j] = (char **)malloc(sizeof(char *) * 3);
        if (!cmds[j])
        {
            ft_free_2d_arr(cmds[j]);
            exit(EXIT_FAILURE);
        }
        ft_printf("pipex->args[%d]: %s\n", i, pipex->args[i]);
        ft_printf("pipex->args[%d]: %s\n", i + 1, pipex->args[i + 1]);
        cmds[j][0] = ft_strdup(pipex->args[i]);
        cmds[j][1] = ft_strdup(pipex->args[i + 1]);
        cmds[j][2] = NULL;

        i += 2;
        j++;
    }
    cmds[j] = NULL;
    // ft_printf("\ncmds set\n");
    // ft_printf("cmds[0][0]: %s\n", cmds[0][0]);
    // ft_printf("cmds[0][1]: %s\n", cmds[0][1]);
    // ft_printf("cmds[0][2]: %s\n", cmds[0][2]);
    // ft_printf("cmds[1][0]: %s\n", cmds[1][0]);
    // ft_printf("cmds[1][1]: %s\n", cmds[1][1]);
    // ft_printf("cmds[1][2]: %s\n", cmds[1][2]);
    // ft_printf("cmds[1][2]: %s\n", cmds[1][2]);
    // ft_printf("cmds[2][0]: %s\n", cmds[2][0]);
    return (cmds);
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
