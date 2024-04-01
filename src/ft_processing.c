#include "pipex.h"

char *find_path(char **directories, char *cmd);

int ft_processing(t_pipex *pipex)
{
    int status;
    char *left_pid_path;
    char *right_pid_path;
    ft_printf("left pid args  -> %s\n", pipex->args[0]);
    ft_printf("left pid cmd   -> %s, flag %s\n", pipex->cmds[0][0], pipex->cmds[0][1]);
    ft_printf("right pid args -> %s\n", pipex->args[2]);
    ft_printf("right pid cmd  -> %s, flag %s\n", pipex->cmds[1][0], pipex->cmds[1][1]);

    pipex->pid_left = fork();
    if (pipex->pid_left == -1)
    {
        perror("ft_processing:");
        exit(EXIT_FAILURE);
    }
    if (pipex->pid_left == 0)
    {
        // equivalent < infile.txt
        if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
        {
            perror("left pid file in");
            exit(EXIT_FAILURE);
        }
        close(pipex->infile_fd);
        // send output to pipe
        if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("left pid pipe out");
            exit(EXIT_FAILURE);
        }
        left_pid_path = find_path(pipex->directories, pipex->args[0]);
        execve(left_pid_path, pipex->cmds[0], NULL);
        close(pipex->pipe_fd[1]);
    }

    pipex->pid_right = fork();
    // ft_printf("right children pid -> %d\n", pipex->pid_right);
    if (pipex->pid_right == -1)
    {
        perror("ft_processing:");
        exit(EXIT_FAILURE);
    }
    if (pipex->pid_right == 0)
    {
        // pipe routing from another child
        if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
        {
            perror("right pid pipe in");
            exit(EXIT_FAILURE);
        }
        // equivalent > outfile.txt
        if (dup2(STDOUT_FILENO, pipex->outfile_fd) == -1)
        {
            perror("right pid file out");
            exit(EXIT_FAILURE);
        }
        right_pid_path = find_path(pipex->directories, pipex->args[2]);
        execve(right_pid_path, pipex->cmds[2], NULL);
        close(pipex->pipe_fd[0]);
    }
    waitpid(pipex->pid_left, &status, 0);
    waitpid(pipex->pid_right, &status, 0);
    return (EXIT_SUCCESS);
}

char *find_path(char **directories, char *cmd)
{
    char *path;
    int i;

    i = -1;
    while (directories[++i] != NULL)
    {
        path = ft_strjoin(directories[i], "/");
        path = ft_strjoin(path, cmd);
        if (access(path, F_OK | X_OK) == 0)
        {
            ft_printf("path found\n");
            return (path);
        }
        free(path);
        path = NULL;
    }
    return (NULL);
}
char ***ft_set_cmds(t_pipex *pipex)
{
    static char ***cmds;
    static int cmd_count, i, j;

    i = 0;
    j = 0;
    cmd_count = pipex->args_count / 2;
    cmds = (char ***)malloc(sizeof(char **) * (cmd_count + 1));
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
