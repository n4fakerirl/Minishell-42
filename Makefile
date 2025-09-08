# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:51:02 by ocviller          #+#    #+#              #
#    Updated: 2025/09/08 17:05:32 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME        = minishell

# Compilateur et flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -I. -Ilibft

# Librairies à linker
LIBS        = -lreadline -lncurses

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# Fichiers sources
SRC         = main.c token.c utils.c

# Objets générés
OBJ         = $(SRC:.c=.o)

# Règle par défaut
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilation des .o
%.o: %.c minishell.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
