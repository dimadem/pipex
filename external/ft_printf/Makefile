#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 12:40:43 by dmdemirk          #+#    #+#              #
#    Updated: 2023/12/18 12:28:14 by dmdemirk         ###   ########.fr        #
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

# Actions

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -g
RM				=	rm -rf
AR				=	ar rcs

# library
LIBFT_DIR		=	../libft
LIBFT	 		=	$(LIBFT_DIR)/libft.a

# Sources
PRINTF_DIR		=	./ft_printf
NAME				=	libftprintf.a
FT_PRINTF_SRC_FILES	=	ft_printf.c					\
						ft_printf_hexadecimal.c		\
						ft_printf_pointer.c			\
						ft_printf_unsigned.c		\
						ft_printf_utils.c
					
OBJS				=	$(FT_PRINTF_SRC_FILES:%.c=%.o)

# Comands
all:				$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
					@cp $(LIBFT) $(NAME)
					$(AR) $(NAME) $(OBJS)
					@echo "$(GREEN)FT_PRINTF compiled$(DEF_COLOR)"

$(LIBFT):
					@echo "$(YELLOW)LIBFT compilation process"
					@cd $(LIBFT_DIR) && make && echo "$(GREEN)LIBFT compiled$(DEF_COLOR)"
				

%.o: %.c $(INCLUDE)
	@echo "$(YELLOW)FT_PRINTF compilation process"
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
					@$(RM) -rf $(OBJS)
					@cd $(LIBFT_DIR) && make clean
					@echo "$(RED)FT_PRINTF object files cleaned!$(DEF_COLOR)"

fclean:				clean
					@$(RM) -f $(NAME)
					@$(RM) -f $(LIBFT)
					@echo "$(RED)FT_PRINTF executable files cleaned!$(DEF_COLOR)"
					@echo "$(RED)LIBFT executable files cleaned!$(DEF_COLOR)"

re:					fclean all
	@echo "$(CYAN)cleaned and rebuilt everything for ft_printf!$(DEF_COLOR)"

.PHONY:				all clean fclean re
