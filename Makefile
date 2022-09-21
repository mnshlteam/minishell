# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyejo <hyejo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 21:11:25 by hyejo             #+#    #+#              #
#    Updated: 2022/09/21 20:03:22 by hyejo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	minishell

CC			=	gcc# -Wall -Wextra -Werror
LIB_DIR		=	libft
LIB			=	libft/libft.a
SRCS		=	minishell.c directory.c echo.c env_ctrl.c env.c env_error.c exec_cmd.c exec_file.c exec_proc.c execute.c infile_cntl.c outfile_cntl.c parse.c parse_dollar.c parse_quotes.c parse_redirect.c split_str.c utils.c utils2.c utils3.c 
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
