#include "pipex_bonus.h"

static void ft_null(t_pipex *pipex) {
  pipex->directories = NULL;
  pipex->shift = 0;
  pipex->args_count = 0;
  pipex->cmds_count = 0;
  pipex->args = NULL;
  pipex->cmds = NULL;
  pipex->infile = NULL;
  pipex->outfile = NULL;
  pipex->infile_fd = -1;
  pipex->outfile_fd = -1;
  pipex->here_doc = 0;
}

void ft_init(t_pipex *pipex, int *argc, char **argv, char **envp) {
  ft_null(pipex);
  pipex->directories = ft_parse_path(envp);
  // ft_printf("pipex->args_count: %d\n", pipex->args_count);
  pipex->shift = 2;
  // ft_printf("\n**ft_parse_args**\n");
  pipex->args = ft_parse_args(pipex, argc, argv);
  pipex->cmds = ft_set_cmds(pipex);
  // print pipex args list
  // while (*pipex->args) {
  //   ft_printf("pipex->args: %s\n", *pipex->args);
  //   pipex->args++;
  // }
  // write(1, "\n", 1);
  pipex->infile = pipex->args[1];
  pipex->outfile = pipex->args[(*argc) - 1];
  // open files
  ft_open_file(pipex);
}
