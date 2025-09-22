# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/09/22 12:20:17 by lenakach         ###   ########.fr        #
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
EXEC_DIR = exec
LIBFT_DIR = libft

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
BUITLINS = $(BUITLINS_DIR)/env.c $(BUITLINS_DIR)/echo.c $(BUITLINS_DIR)/pwd.c $(BUITLINS_DIR)/cd.c \
			$(BUITLINS_DIR)/exit.c $(BUITLINS_DIR)/export.c $(BUITLINS_DIR)/unset.c $(BUITLINS_DIR)/exit_builtins.c \

UTILS = $(UTILS_DIR)/init_struct.c $(UTILS_DIR)/divers.c $(UTILS_DIR)/free.c $(UTILS_DIR)/init_cmd.c

EXEC = $(EXEC_DIR)/exec_builtins.c $(EXEC_DIR)/exec_start.c $(EXEC_DIR)/path.c $(EXEC_DIR)/first_pipe.c \
		$(EXEC_DIR)/last_pipe.c $(EXEC_DIR)/exec_utils.c $(EXEC_DIR)/one_cmd.c $(EXEC_DIR)/inter_pipe.c \
		$(EXEC_DIR)/exit_exec.c
SRCS = $(EXEC) $(BUITLINS) $(UTILS) main.c
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