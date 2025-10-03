# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 12:51:02 by ocviller          #+#    #+#              #
#    Updated: 2025/10/03 17:04:37 by ocviller         ###   ########.fr        #
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

# Dossier pour les objets
OBJ_DIR     = obj

# Fichiers sources
SRC         = main.c token.c utils.c parsing.c expand.c split2.c

# Objets générés dans le dossier obj/
OBJ         = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Règle par défaut
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Création du dossier obj/ s'il n'existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation des .o dans le dossier obj/
$(OBJ_DIR)/%.o: %.c minishell.h libft/libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re