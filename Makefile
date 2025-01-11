# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 11:55:48 by fde-sist          #+#    #+#              #
#    Updated: 2025/01/11 10:56:23 by fde-sist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Source files with full paths
SRCS = src/main.c src/builtins/cd.c src/builtins/pwd.c src/builtins/env.c src/builtins/echo.c src/builtins/export.c src/builtins/unset.c \
	   src/env/envp.c src/env/add_env_var.c\
	   src/parser/parse.c \
	   src/memory_managment/free_string_array.c

# Object files will all go in obj/ directory
OBJ_DIR = obj
# Create object file names by replacing src/ with obj/ and .c with .o
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wmaybe-uninitialized

LIBS = -lreadline -lncurses -lft

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

# Create subdirectories in obj/ as needed
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtins

clean:
	@rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
