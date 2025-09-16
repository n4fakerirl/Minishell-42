# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/09/16 13:22:22 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = minishell

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
BUITLINS_DIR = builtins
UTILS_DIR = utils
CMD_DIR = commands
LIBFT_DIR = libft

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
BUITLINS = $(BUITLINS_DIR)/env.c $(BUITLINS_DIR)/echo.c $(BUITLINS_DIR)/pwd.c $(BUITLINS_DIR)/cd.c \
			$(BUITLINS_DIR)/exit.c $(BUITLINS_DIR)/export.c $(BUITLINS_DIR)/unset.c $(BUITLINS_DIR)/exit_builtins.c \
			$(BUITLINS_DIR)/exec_builtins.c
UTILS = $(UTILS_DIR)/init_struct.c $(UTILS_DIR)/divers.c $(UTILS_DIR)/free.c

COMMANDS = 
SRCS = $(BUITLINS) $(UTILS) main.c
OBJS = $(SRCS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all : $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de Libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

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