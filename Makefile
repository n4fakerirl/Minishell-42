# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/09/08 15:23:49 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = minishell

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror

#Dossiers
SRC_DIR = builtins
LIBFT_DIR = libft

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
SRC = $(SRC_DIR)/env.c $(SRC_DIR)/echo.c $(SRC_DIR)/pwd.c $(SRC_DIR)/cd.c

SRCS = $(SRC) main.c
OBJS = $(SRCS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all : $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de Libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

#bonus: $(LIBFT) $(NAME_BONUS)

#$(NAME_BONUS): $(OBJS_BONUS)
#	$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test