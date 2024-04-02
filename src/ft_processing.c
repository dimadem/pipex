#include "pipex.h"

char *find_path(char **directories, char *cmd);

int ft_processing(t_pipex *pipex)
{
    int left_status, right_status;
    pid_t left_pid, right_pid;
    char *left_pid_path;
    char *right_pid_path;
    // ft_printf("left pid args  -> %s\n", pipex->args[0]);
    // ft_printf("left pid cmd   -> %s, flag -> %s\n", pipex->cmds[0][0], pipex->cmds[0][1]);
    // ft_printf("right pid args -> %s\n", pipex->args[2]);
    // ft_printf("right pid cmd  -> %s, flag -> %s\n", pipex->cmds[1][0], pipex->cmds[1][1]);

    left_pid = fork();
    if (left_pid == -1)
    {
        perror("left pid fork");
        exit(EXIT_FAILURE);
    }
    if (left_pid == 0)
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
        close(pipex->pipe_fd[0]);
        close(pipex->pipe_fd[1]);
        left_pid_path = find_path(pipex->directories, pipex->args[0]);
        if (left_pid_path == NULL)
        {
            perror("left pid path not found");
            exit(EXIT_FAILURE);
        }
        execve(left_pid_path, pipex->cmds[0], NULL);
        perror("left pid execve");
        exit(EXIT_FAILURE);
    }

    right_pid = fork();
    // ft_printf("right children pid -> %d\n", pipex->pid_right);
    if (right_pid == -1)
    {
        perror("right pid fork");
        exit(EXIT_FAILURE);
    }
    if (right_pid == 0)
    {
        // pipe routing from another child
        if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
        {
            perror("right pid pipe in");
            exit(EXIT_FAILURE);
        }
        close(pipex->pipe_fd[0]);
        close(pipex->pipe_fd[1]);
        // equivalent > outfile.txt
        if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
        {
            perror("right pid file out");
            exit(EXIT_FAILURE);
        }
        close(pipex->outfile_fd);
        right_pid_path = find_path(pipex->directories, pipex->args[2]);
        if (right_pid_path == NULL)
        {
            perror("right pid path not found");
            exit(EXIT_FAILURE);
        }
        execve(right_pid_path, pipex->cmds[1], NULL);
        perror("right pid execve");
        exit(EXIT_FAILURE);
    }
    close(pipex->pipe_fd[0]);
    close(pipex->pipe_fd[1]);
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
    if (WIFEXITED(left_status) && WIFEXITED(right_status))
    {
        if ((WEXITSTATUS(left_status)) != 0 || (WEXITSTATUS(right_status)) != 0)
            return (EXIT_FAILURE);
    }
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
            // ft_printf("path found\n");
            return (path);
        }
        free(path);
    }
    return (NULL);
}
