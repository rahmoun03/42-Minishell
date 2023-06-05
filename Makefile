# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/05 18:33:48 by arahmoun          #+#    #+#              #
#    Updated: 2023/05/27 19:40:27 by arahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c parser/error.c parser/tools.c parser/linked_list.c parser/ft_split.c \
	parser/split_special.c parser/double_quotes.c parser/expand_vrbs.c parser/herdog.c \
	parser/ft_itoa.c parser/redir.c execution/exec.c execution/get_path.c execution/tools.c\
	execution/exec_tool.c builtins/echo.c builtins/pwd.c builtins/cd.c builtins/export.c \
	execution/ft_redirections.c execution/check_redi.c builtins/exit.c tools.c parser/expand_vrbs2.c\
	 builtins/tools.c tools2.c builtins/unset.c builtins/split_var.c\
	builtins/unset_tools.c execution/commande_tools.c execution/pipes_tools.c execution/ft_init_tools.c\
	parser/get_path.c execution/fd_tools.c builtins/export_tools.c builtins/export_tools2.c\
	builtins/builtins_tools.c parser/lexer.c parser/lexer2.c parser/free.c parser/redir_tools1.c\
	parser/redir_tools2.c parser/spliit_tool.c parser/pid.c parser/pid_tools.c builtins/cd_tools.c
	 
WAJDI_INCLUDE = -L /Users/moazzedd/goinfre/homebrew/Cellar/readline/8.2.1/lib
AYOUB_INCLUDE= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

CFLAGS = -Wall -Wextra -Werror

BREW_FLAGS = -lreadline $(AYOUB_INCLUDE)

all : ${NAME}

${NAME} : ${SRC}
	cc  ${CFLAGS} ${BREW_FLAGS} ${SRC} -o minishell
clean :
	rm -rf minishell
fclean : clean

re : fclean all
