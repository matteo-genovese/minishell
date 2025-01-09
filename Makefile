# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 11:55:48 by fde-sist          #+#    #+#              #
#    Updated: 2025/01/09 12:37:37 by fde-sist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Definiamo i file sorgenti mantenendo i percorsi originali
SRCS = src/main.c

# Cartella per gli oggetti
OBJ_DIR = obj

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Variabile OBJS per i file oggetto dentro obj (file .o saranno tutti in obj/)
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBS = -lreadline -lncurses -lft

all: $(LIBFT) $(NAME)

# Obiettivo principale: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

# Creazione della cartella obj se non esiste
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Regola generica per compilare ogni file sorgente, indipendentemente dalla directory di origine
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Regola per trovare i file .c originali nelle sottocartelle
vpath %.c $(sort $(dir $(SRCS)))


clean:
	@rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re