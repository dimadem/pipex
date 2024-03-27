#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../external/ft_printf/src/ft_printf.h"

typedef struct s_pipex
{
    char **cmd;
    char *infile;
    char *outfile;
    int infile_fd;
    int outfile_fd;
    int pipe_fd[2];
} t_pipex;

int ft_parse_cmd(t_pipex *pipex, char **envp);
int ft_open_files(t_pipex *pipex);
void ft_free_cmd(char **array);
void ft_free_pipex(t_pipex *pipex);

#endif
