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

# Colors

DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

NAME				=	pipex

COMPILER			=	gcc
FLAGS				=	-Wall -Wextra -Werror
AR					=	ar rcs

# external
EXTERNAL_DIR		=	./external
FT_PRINTF			=	$(EXTERNAL_DIR)/ft_printf/ft_printf.a
INCLUDES			=	-I$(EXTERNAL_DIR)/ft_printf/src/

# src
SRC_DIR				=	./src
SOURCES				=	/main.c			\
						/pipex.c		\
						/utils.c	\
# SOURCES_BONUS		=	
SOURCES				:=	$(addprefix $(SRC_DIR)/, $(SOURCES))

# build
BUILD_DIR 			=	./build
OBJS				=	$(SOURCES:%.c=$(BUILD_DIR)/%.o)
OBJS_BONUS			=	$(SOURCES_BONUS:%.c=$(BUILD_DIR)/%.o)

all: 					$(NAME)

$(NAME): $(FT_PRINTF)
						@echo "$(WHITE)Building pipex"
						@mkdir -p $(BUILD_DIR)
						@$(COMPILER) $(FLAGS) $(INCLUDES) $(SOURCES) $(LIBFT) $(FT_PRINTF) -o $(NAME)
						@echo "$(GREEN)Pipex built$(DEF_COLOR)"
$(FT_PRINTF):
						@cd $(EXTERNAL_DIR)/ft_printf && make 

$(BUILD_DIR)/%.o:		$(SRC_DIR)/%.c

clean:
						@echo "$(RED)Cleaning process"
						@cd $(EXTERNAL_DIR)/ft_printf && make clean
						@rm -rf $(BUILD_DIR)
						@echo "$(GREEN)Cleaning process done$(DEF_COLOR)"

fclean:					clean
						@echo "$(RED)Full cleaning process"
						@cd $(EXTERNAL_DIR)/ft_printf && make fclean
						@rm -rf $(NAME)
						@echo "$(GREEN)Full cleaning process done$(DEF_COLOR)"

re:						fclean all
						@echo "$(CYAN)cleaned and rebuilt everything for pipex!$(DEF_COLOR)"


.PHONY:					all clean fclean re