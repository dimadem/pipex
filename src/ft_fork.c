#include "pipex.h"

int ft_fork(t_pipex *pipex)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error: Failed to fork process\n");
        return (-1);
    }
    if (pid == 0)
    {
        if (pipex->infile_fd != -1)
        {
            if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
            {
                perror("Error: Failed to duplicate file descriptor\n");
                return (-1);
            }
        }
        else if (pipex->pipe_fd[0] != -1)
        {
            if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
            {
                perror("Error: Failed to duplicate file descriptor\n");
                return (-1);
            }
        }
        if (pipex->outfile_fd != -1)
        {
            if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
            {
                perror(" Error: Failed to duplicate file descriptor\n");
                return (-1);
            }
        }
        else if (pipex->pipe_fd[1] != -1)
        {
            if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
            {
                perror(" Error: Failed to duplicate file descriptor\n");
                return (-1);
            }
        }
        if (pipex->infile_fd != -1)
            close(pipex->infile_fd);
        if (pipex->outfile_fd != -1)
            close(pipex->outfile_fd);
        if (pipex->pipe_fd[0] != -1)
            close(pipex->pipe_fd[0]);
        if (pipex->pipe_fd[1] != -1)
            close(pipex->pipe_fd[1]);
        execve(pipex->cmd[0], pipex->cmd, ((void *)0));
        perror(" Error: Failed to execute command\n");
        return (-1);
    }
    else
    {
        waitpid(pid, &status, 0);
        return (0);
    }
}
