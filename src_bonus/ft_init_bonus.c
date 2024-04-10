#include "pipex_bonus.h"

static void ft_null(t_pipex *pipex) {
  pipex->directories = NULL;
  pipex->args_count = 0;
  pipex->cmds_count = 0;
  pipex->args = NULL;
  pipex->cmds = NULL;
  pipex->infile = NULL;
  pipex->outfile = NULL;
  pipex->infile_fd = -1;
  pipex->outfile_fd = -1;
  pipex->here_doc = -1;
}

void ft_init(t_pipex *pipex, int *argc, char **argv, char **envp) {
  ft_null(pipex);
  pipex->directories = ft_parse_path(envp);
  pipex->args = ft_parse_args(pipex, argc, argv);
  pipex->here_doc =
      ft_strncmp(pipex->args[1], "here_doc", ft_strlen("here_doc"));
  ft_printf("here_doc -> %d\n", pipex->here_doc);
  pipex->cmds = ft_set_cmds(pipex);
  pipex->infile = pipex->args[1];
  pipex->outfile = pipex->args[(*argc) - 1];
  ft_open_file(pipex);
}
