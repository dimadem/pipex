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

#endif
