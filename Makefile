# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 18:35:51 by dmdemirk          #+#    #+#              #
#    Updated: 2024/04/10 15:24:22 by dmdemirk         ###   ########.fr        #
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
NAME_BONUS			=	pipex_bonus

COMPILER			=	cc
FLAGS				=	-Wall -Wextra -Werror -g
AR					=	ar rcs

# external
EXTERNAL_DIR		=	./external
FT_PRINTF			=	$(EXTERNAL_DIR)/ft_printf/ft_printf.a
INCLUDES			=	-I$(EXTERNAL_DIR)/ft_printf/src/

# src
SRC_DIR				=	./src
SRC_BONUS_DIR		=	./src_bonus
SOURCES				=	$(wildcard $(SRC_DIR)/*.c)
								       SOURCES_BONUS		=	$(wildcard $(SRC_BONUS_DIR)/*.c)

# build 
BUILD_DIR 			=	./build
OBJS 				= 	$(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:%.c=%.o)))
OBJS_BONUS			=	$(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES_BONUS:%.c=%.o)))

all: 					$(NAME)

$(NAME):	$(FT_PRINTF) $(OBJS)
	@echo "$(WHITE)Building pipex"
	@$(COMPILER) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(FT_PRINTF)
	@file $(NAME)
	@echo "$(GREEN)Pipex built$(DEF_COLOR)"

$(OBJS):	$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

bonus:	$(FT_PRINTF) $(OBJS_BONUS)
	@echo "$(MAGENTA)Building pipex"
	@$(COMPILER) $(FLAGS) $(INCLUDES) $(OBJS_BONUS) -o $(NAME_BONUS) $(FT_PRINTF)
	@file $(NAME_BONUS)
	@echo "$(GREEN)Pipex bonus part built$(DEF_COLOR)"

$(OBJS_BONUS):	$(BUILD_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

$(FT_PRINTF):
	@cd $(EXTERNAL_DIR)/ft_printf && make 

clean:
	@echo "$(RED)Cleaning process"
	@cd $(EXTERNAL_DIR)/ft_printf && make clean
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)Cleaning process done$(DEF_COLOR)"

fclean:		clean
	@echo "$(RED)Full cleaning process"
	@cd $(EXTERNAL_DIR)/ft_printf && make fclean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)Full cleaning process done$(DEF_COLOR)"

re:		fclean all
	@echo "$(CYAN)cleaned and rebuilt everything for pipex!$(DEF_COLOR)"


.PHONY:		all clean fclean re
