#include "pipex_bonus.h"

char **ft_parse_args(t_pipex *pipex, int *argc, char **argv) {
  char **args;
  int i;
  ft_printf("\nft_parse_args\n");
  ft_printf("argc               -> %d\n", *argc);
  args = (char **)malloc(sizeof(char **) * (*argc + 1));
  if (!args)
    exit(EXIT_FAILURE);
  i = 0;
  while (i < *argc) {
    ft_printf("args[%d]         -> %s\n", (i), argv[i]);
    args[i] = ft_strdup(argv[i]);
    if (!args[i]) {
      exit(EXIT_FAILURE);
    }
    i++;
  }
  pipex->args_count = i;
  args[i] = NULL;
  return (args);
}

char **ft_parse_path(char **envp) {
  char *path = NULL;
  char **directories = NULL;
  int i;

  i = -1;
  while (*envp[++i]) {
    if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
      path = ft_strdup(envp[i] + 5);
      if (!path)
        exit(EXIT_FAILURE);
      break;
    }
  }
  directories = ft_split(path, ':');
  if (!directories) {
    free(path);
    return (NULL);
  }
  free(path);
  return (directories);
}

char ***ft_set_cmds(t_pipex *pipex) {
  char ***cmds;
  int i, j;
  int shift, files;
  i = 0;
  j = 0;
  if (pipex->here_doc == 0) {
    files = 4;
    shift = 3;
  } else {
    files = 3;
    shift = 2;
  }
  ft_printf("\nft_set_cmds\n");
  ft_printf("pipex->args_count %d\n", pipex->args_count);
  ft_printf("files             %d\n", files);
  ft_printf("args shift        %d\n", shift);
  cmds = (char ***)malloc(sizeof(char **) *
                          (((pipex->args_count - files) / 2) + 1));
  if (!cmds)
    exit(EXIT_FAILURE);
  while (i < pipex->args_count - files) {
    ft_printf("cmds[%d] malloc\n", j);
    cmds[j] = (char **)malloc(sizeof(char *) * 3);
    if (!cmds[j]) {
      exit(EXIT_FAILURE);
    }

    cmds[j][0] = ft_strdup(pipex->args[shift + i]);
    cmds[j][1] = ft_strdup(pipex->args[shift + i + 1]);
    cmds[j][2] = NULL;
    ft_printf("cmds[%d][0] -> %s\n", j, cmds[j][0]);
    ft_printf("cmds[%d][1] -> %s\n", j, cmds[j][1]);
    ft_printf("cmds[%d][2] -> %s\n", j, cmds[j][2]);
    i += 2;
    j++;
  }
  pipex->cmds_count = j;
  cmds[j] = NULL;
  return (cmds);
}

int ft_open_file(t_pipex *pipex) {
  if (pipex->here_doc == 0) {
    pipex->infile_fd = 0;
    pipex->outfile_fd =
        open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
  } else {
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    pipex->outfile_fd =
        open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  }
  if (pipex->infile_fd == -1) {
    ft_printf("Error: Failed to open infile\n");
    exit(EXIT_FAILURE);
  }
  if (pipex->outfile_fd == -1) {
    ft_printf("Error: Failed to open outfile\n");
    exit(EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

void ft_close_all_pipes(t_pipex *pipex, int pipes[][2]) {
  int j;

  j = 0;
  while (j < pipex->cmds_count) {
    close(pipes[j][0]);
    close(pipes[j][1]);
    ++j;
  }
}
