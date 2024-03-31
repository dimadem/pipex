#include "pipex.h"

int ft_processing(t_pipex *pipex)
{
    int status;

    pipex->pid_left = fork();
    ft_printf("left children pid -> %d\n", pipex->pid_left);
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
        execve(pipex->args[0], &pipex->cmds[0], NULL);
        close(pipex->pipe_fd[1]);
    }

    pipex->pid_right = fork();
    ft_printf("right children pid -> %d\n", pipex->pid_right);
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
        execve(pipex->args[1], &pipex->cmds[1], NULL);
        close(pipex->pipe_fd[0]);
    }

    ft_printf("OUTFILE -> %s\n", pipex->outfile);
    waitpid(pipex->pid_left, &status, 0);
    waitpid(pipex->pid_right, &status, 0);
    return (EXIT_SUCCESS);
}