# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 18:35:51 by dmdemirk          #+#    #+#              #
#    Updated: 2024/03/18 18:40:25 by dmdemirk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex

COMPILER			=	gcc
FLAGS				=	-Wall -Wextra -Werror
AR					=	ar rcs

# external
EXTERNAL_DIR		=	./external
LIBFT				=	libft.h
PRINTF				=	ft_printf.h

# src
SRC_DIR				=	./src
SOURCES				=	$(SRC_DIR)/main.c			\
						$(SRC_DIR)/pipex.c			\
						$(SRC_DIR)/pipex_utils.c	\
SOURCES_BONUS		=	

# build
BUILD_DIR 			=	./build
OBJS				=	$(SOURCES:%.c=$(BUILD_DIR)/%.o)
OBJS_BONUS			=	$(SOURCES_BONUS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
