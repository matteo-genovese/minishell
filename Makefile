# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: starry <starry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 11:55:48 by fde-sist          #+#    #+#              #
#    Updated: 2025/02/18 13:18:36 by starry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRCS = src/main.c src/builtins/cd.c src/builtins/pwd.c src/builtins/env.c src/builtins/echo.c src/builtins/export.c src/builtins/unset.c src/builtins/exit.c \
	   src/env/envp.c src/env/add_env_var.c src/env/set_shell_level.c \
	   src/parser/parse.c src/parser/quote_utils.c src/parser/parser_utils.c src/parser/preprocessing.c src/parser/exotic_char_utils.c src/parser/envp_preprocessing.c \
	   src/memory_managment/free_string_array.c \
	   src/command_execution/command_utils.c src/command_execution/find_path.c src/command_execution/execute_command.c src/command_execution/command_setting.c src/command_execution/set_command_info.c src/command_execution/fork_processes.c src/command_execution/heredoc.c\
	   src/signals/signal_handler.c
CFLAGS = -Wall -Wextra -Werror -g -Wmaybe-uninitialized -Wuninitialized

LIBFT_DIR = ./libs/libft
HEADERS = -I./headers -I$(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)/libft.a
LINK = -lreadline -lncurses $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(HEADERS) $(SRCS) $(LINK) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus

clean:
	@rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

valgrind:
	valgrind --show-leak-kinds=all --leak-check=full -s ./$(NAME)

.PHONY: all clean fclean re
