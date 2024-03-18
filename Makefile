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
AR				=	ar rcs

LIBFT				=	libft.h
SOURCES				=	
SOURCES_BONUS			=	

OBJS				=
OBJS_BONUS			=	

all: $(NAME)

$(NAME): $(OBJS)
