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

  i = 0;
  j = 0;
  ft_printf("\nft_set_cmds\n");
  ft_printf("pipex->args_count %d\n", pipex->args_count);
  ft_printf("pipex->shift %d\n", pipex->shift);
  cmds =
      (char ***)malloc(sizeof(char **) * (((pipex->args_count - 3) / 2) + 1));
  if (!cmds)
    exit(EXIT_FAILURE);
  while (i < pipex->args_count - 3) {
    cmds[j] = (char **)malloc(sizeof(char *) * 3);
    if (!cmds[j]) {
      exit(EXIT_FAILURE);
    }
    ft_printf("pipex->args[%d]: %s\n", i, pipex->args[i]);
    ft_printf("pipex->args[%d]: %s\n", i + 1, pipex->args[i + 1]);
    cmds[j][0] = ft_strdup(pipex->args[i + pipex->shift]);
    cmds[j][1] = ft_strdup(pipex->args[i + 1 + pipex->shift]);
    cmds[j][2] = NULL;
    i += 2;
    j++;
  }
  pipex->cmds_count = j;
  cmds[j] = NULL;
  ft_printf("\ncmds set\n");
  ft_printf("cmds[0][0]: %s\n", cmds[0][0]);
  ft_printf("cmds[0][1]: %s\n", cmds[0][1]);
  ft_printf("cmds[0][2]: %s\n", cmds[0][2]);
  ft_printf("cmds[1][0]: %s\n", cmds[1][0]);
  ft_printf("cmds[1][1]: %s\n", cmds[1][1]);
  ft_printf("cmds[1][2]: %s\n", cmds[1][2]);
  // ft_printf("cmds[2][0]: %s\n", cmds[2][0]);
  // ft_printf("cmds[2][1]: %s\n", cmds[2][1]);
  // ft_printf("cmds[2][2]: %s\n", cmds[2][2]);
  return (cmds);
}

int ft_open_file(t_pipex *pipex) {
  pipex->infile_fd = open(pipex->infile, O_RDONLY);
  if (pipex->infile_fd == -1) {
    ft_printf("Error: Failed to open infile\n");
    exit(EXIT_FAILURE);
  }
  pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (pipex->outfile_fd == -1) {
    ft_printf("Error: Failed to open outfile\n");
    exit(EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

// int **ft_create_pipes(t_pipex *pipex) {
//   int **result;
//   int i;

//   i = 0;
//   result = (int **)malloc(sizeof(int *) * ((pipex->args_count / 2) + 1));
//   if (!result)
//     exit(EXIT_FAILURE);
//   while (i < (pipex->args_count / 2)) {
//     result[i] = (int *)malloc(sizeof(int) * 2);
//     if (!result[i])
//       exit(EXIT_FAILURE);
//     ft_printf("creating pipe [%d]\n", i);
//     if (pipe(result[i]) == -1) {
//       ft_printf("Error: Failed to create pipe\n");
//       exit(EXIT_FAILURE);
//     }
//     i++;
//   }
//   result[i] = ((void *)0);
//   return (result);
// }

void ft_close_all_pipes(t_pipex *pipex, int pipes[][2]) {
  int j;

  j = 0;
  while (j < pipex->args_count / 2) {
    close(pipes[j][0]);
    close(pipes[j][1]);
    ++j;
  }
}
