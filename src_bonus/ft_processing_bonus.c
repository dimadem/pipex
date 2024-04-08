#include "pipex_bonus.h"
#include <sys/wait.h>

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
  pids[i] = fork();
  if (pids[i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pids[i] == 0) {
    // child process
    close(pipes[1][0]);
    close(pipes[1][1]);
    close(pipes[0][0]);
    dup2(pipex->infile_fd, STDIN_FILENO);
    dup2(pipes[0][1], STDOUT_FILENO);
    ft_close_all_pipes(pipex, pipes);
    char *path = find_path(pipex->directories, pipex->args[i]);
    execve(path, pipex->cmds[i], envp);
    perror("execve");
    exit(EXIT_FAILURE);
  }
  // -> cmd2 -> ... -> cmdN ->
  while (++i < pipex->args_count / 2) {
    ft_printf("args [%d] -> %s\n", i, pipex->args[i * 2]);
    // last cmd -> file out
    if (i == pipex->args_count / 2 - 1) {
      pids[i] = fork();
      if (pids[i] == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      }
      if (pids[i] == 0) {
        // -> file out
        dup2(pipes[i - 1][0], STDIN_FILENO);
        dup2(pipex->outfile_fd, STDOUT_FILENO);
        ft_close_all_pipes(pipex, pipes);
        close(pipex->outfile_fd);
        char *path = find_path(pipex->directories, pipex->args[i * 2]);
        execve(path, pipex->cmds[i], envp);
        perror("execve");
        exit(EXIT_FAILURE);
      }
    } else {
      pids[i] = fork();
      if (pids[i] == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      }
      if (pids[i] == 0) {
        close(pipes[i - 1][1]);
        dup2(pipes[i - 1][0], STDIN_FILENO);
        dup2(pipes[i][1], STDOUT_FILENO);
        ft_close_all_pipes(pipex, pipes);
        char *path = find_path(pipex->directories, pipex->args[i * 2]);
        execve(path, pipex->cmds[i], envp);
        perror("execve");
        exit(EXIT_FAILURE);
      }
    }
  }
  ft_close_all_pipes(pipex, pipes);
  int j = -1;
  while (++j < pipex->args_count / 2)
    waitpid(pids[j], &status[j], 0);
  return (EXIT_SUCCESS);
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
