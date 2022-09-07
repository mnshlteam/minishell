# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 21:11:25 by hyejo             #+#    #+#              #
#    Updated: 2022/09/07 16:42:07 by hyejo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	minishell

CC			=	gcc -Wall -Wextra -Werror
LIB_DIR		=	libft
LIB			=	libft/libft.a
SRCS		=	minishell.c directory.c echo.c env_ctrl.c env.c execute.c tmp_parse.c utils.c
OBJS		=	$(SRCS:.c=.o)
LIBFT		=	-Llibft -lft
# RL			=	-lreadline -L/opt/homebrew/opt/readline/lib
# RL_INC		=	-I/opt/homebrew/opt/readline/include
RL			=	-lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib
RL_INC		=	-I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include

$(NAME):  $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(RL) $(RL_INC)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

.c.o:
	@$(CC) -c $< -o $@ $(RL_INC)

all: $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
