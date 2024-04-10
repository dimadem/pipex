#include "pipex_bonus.h"
#include <sys/wait.h>

void ft_infile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i);
void ft_here_doc_fork(t_pipex *pipex, int pipe[][2], pid_t *pid, int *i);
void ft_outfile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                     int *i);
void ft_middle_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i);
char *find_path(char **directories, char *cmd);

int ft_processing(t_pipex *pipex, char **envp) {
  int pipes[pipex->cmds_count - 1][2];
  pid_t pids[pipex->cmds_count];
  int status[pipex->cmds_count];
  int i;
  ft_printf("\nft_processing\n");
  ft_printf("cmds_count        -> %d\n", pipex->cmds_count);
  i = 0;
  // create pipes
  while (i <= pipex->cmds_count) {
    if (pipe(pipes[i]) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
    ++i;
  }
  i = 0;
  // file in -> cmd1 ->
  if (pipex->here_doc == 0)
    ft_here_doc_fork(pipex, pipes, pids, &i);
  else
    ft_infile_fork(pipex, envp, pipes, pids, &i);
  ft_printf("cmds[%d][0]        -> %s\n", i, pipex->cmds[i][0]);
  // -> cmd2 -> ... -> cmdN ->
  while (++i < pipex->cmds_count) {
    ft_printf("cmds[%d][0]        -> %s\n", i, pipex->cmds[i][0]);
    // last cmd -> file out
    if (i == pipex->cmds_count - 1) {
      ft_outfile_fork(pipex, envp, pipes, pids, &i);
    } else {
      ft_middle_fork(pipex, envp, pipes, pids, &i);
    }
  }
  ft_close_all_pipes(pipex, pipes);
  i = -1;
  while (++i < pipex->cmds_count)
    waitpid(pids[i], &status[i], 0);
  return (EXIT_SUCCESS);
}

void ft_here_doc_fork(t_pipex *pipex, int pipe[][2], pid_t *pid, int *i) {
  char *line;

  pid[*i] = fork();
  if (pid[*i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid[*i] == 0) {
    while ((line = ft_get_next_line(STDIN_FILENO)) != NULL) {
      if (ft_strncmp(line, pipex->args[2], ft_strlen(pipex->args[2])) == 0) {
        break;
      }
      write(pipe[0][1], line, ft_strlen(line));
    }
    ft_close_all_pipes(pipex, pipe);
    exit(EXIT_SUCCESS);
  }
}

void ft_infile_fork(t_pipex *pipex, char **envp, int pipe[][2], pid_t *pid,
                    int *i) {
  pid[*i] = fork();
  if (pid[*i] == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid[*i] == 0) {
    dup2(pipex->infile_fd, STDIN_FILENO);
    dup2(pipe[0][1], STDOUT_FILENO);
    close(pipex->infile_fd);
    ft_close_all_pipes(pipex, pipe);
    char *path = find_path(pipex->directories, pipex->cmds[*i][0]);
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
    close(pipex->outfile_fd);
    ft_close_all_pipes(pipex, pipe);
    char *path = find_path(pipex->directories, pipex->cmds[*i][0]);
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
    char *path = find_path(pipex->directories, pipex->cmds[*i][0]);
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

// ./pipex ./test/infile ls -l ls -l ls -l ls -l ls -l wc -l ./test/outfile
