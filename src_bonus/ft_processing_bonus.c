#include "pipex_bonus.h"
#include <sys/wait.h>

void ft_infile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i);
void ft_outfile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                     int *i);
void ft_middle_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i);
char *find_path(char **directories, char *cmd);

int ft_processing(t_pipex *pipex, char **envp) {
  int pipes[pipex->args_count / 2][2];
  pid_t pids[pipex->args_count / 2];
  int status[pipex->args_count / 2];
  int i;

  ft_printf("amount of forks() -> %d\n", (pipex->args_count / 2));
  i = 0;
  // create pipes
  while (i < (pipex->args_count / 2)) {
    if (pipe(pipes[i]) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
    ++i;
  }
  i = 0;
  // file in -> cmd1 ->
  ft_infile_fork(pipex, envp, pipes, pids, &i);
  // -> cmd2 -> ... -> cmdN ->
  while (++i < pipex->args_count / 2) {
    ft_printf("args [%d] -> %s\n", i, pipex->args[i * 2]);
    // last cmd -> file out
    if (i == pipex->args_count / 2 - 1) {
      ft_outfile_fork(pipex, envp, pipes, pids, &i);
    } else {
      ft_middle_fork(pipex, envp, pipes, pids, &i);
    }
  }
  ft_close_all_pipes(pipex, pipes);
  i = -1;
  while (++i < pipex->args_count / 2)
    waitpid(pids[i], &status[i], 0);
  return (EXIT_SUCCESS);
}

// todo
//  1. ft_infile_fork() - done
//  2. ft_outfile_fork() - done
//  3. ft_middle_fork()

void ft_infile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i) {
  // file in -> cmd1 ->
  pid[*i] = fork();
  if (pid[*i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid[*i] == 0) {
    dup2(pipex->infile_fd, STDIN_FILENO);
    dup2(pipe[0][1], STDOUT_FILENO);
    ft_close_all_pipes(pipex, pipe);
    char *path = find_path(pipex->directories, pipex->args[*i]);
    execve(path, pipex->cmds[*i], envp);
    perror("execve");
    exit(EXIT_FAILURE);
  }
}

void ft_outfile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                     int *i) {
  pid[*i] = fork();
  if (pid[*i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid[*i] == 0) {
    dup2(pipe[*i - 1][0], STDIN_FILENO);
    dup2(pipex->outfile_fd, STDOUT_FILENO);
    ft_close_all_pipes(pipex, pipe);
    close(pipex->outfile_fd);
    char *path = find_path(pipex->directories, pipex->args[*i * 2]);
    execve(path, pipex->cmds[*i], envp);
    perror("execve");
    exit(EXIT_FAILURE);
  }
}

void ft_middle_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i) {
  pid[*i] = fork();
  if (pid[*i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid[*i] == 0) {
    dup2(pipe[*i - 1][0], STDIN_FILENO);
    dup2(pipe[*i][1], STDOUT_FILENO);
    ft_close_all_pipes(pipex, pipe);
    char *path = find_path(pipex->directories, pipex->args[*i * 2]);
    execve(path, pipex->cmds[*i], envp);
    perror("execve");
    exit(EXIT_FAILURE);
  }
}

char *find_path(char **directories, char *cmd) {
  char *path;
  int i;

  i = -1;
  while (directories[++i] != ((void *)0)) {
    path = ft_strjoin(directories[i], "/");
    path = ft_strjoin(path, cmd);
    if (access(path, F_OK | X_OK) == 0) {
      ft_printf("path found\n");
      return (path);
    }
    free(path);
  }
  return ((void *)0);
}
