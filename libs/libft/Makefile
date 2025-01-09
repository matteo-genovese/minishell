# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 16:51:14 by fde-sist          #+#    #+#              #
#    Updated: 2024/10/17 17:39:38 by fde-sist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome del progetto
NAME = libft.a

# Compilatore e opzioni
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Lista dei file sorgente
SRC_FILES = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_wlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_long_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strjoin_fw.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			
SRC_FILES_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
# Costruzione della lista di oggetti
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES_BONUS = $(SRC_FILES_BONUS:.c=.o)

# Regole
all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

bonus: $(OBJ_FILES_BONUS)
	ar rcs $(NAME) $(OBJ_FILES_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
