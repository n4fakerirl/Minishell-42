# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/10/08 02:45:07 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = minishell

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
#BUITLINS_DIR = builtins
FREE_DIR = free
EXEC_DIR = exec
LIBFT_DIR = libft
PARS_DIR = parsing
BUITLINS_DIR = builtins
#REDIR_DIR = redir
#HEREDOC_DIR = heredoc

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
BUITLINS = $(BUITLINS_DIR)/env.c $(BUITLINS_DIR)/echo.c $(BUITLINS_DIR)/pwd.c $(BUITLINS_DIR)/cd.c \
			$(BUITLINS_DIR)/exit.c $(BUITLINS_DIR)/export.c $(BUITLINS_DIR)/unset.c $(BUITLINS_DIR)/exit_builtins.c \
			$(BUITLINS_DIR)/builtin_utils.c

FREE = $(FREE_DIR)/free.c $(FREE_DIR)/free_tokens.c
PARSING =  $(PARS_DIR)/cmd_utils.c $(PARS_DIR)/divers.c $(PARS_DIR)/expand_utils.c $(PARS_DIR)/expand_utils2.c \
			$(PARS_DIR)/expand.c $(PARS_DIR)/init_cmd.c $(PARS_DIR)/init_struct.c $(PARS_DIR)/parsing.c \
			$(PARS_DIR)/quote.c $(PARS_DIR)/start_parsing.c $(PARS_DIR)/token_utils.c $(PARS_DIR)/token.c \
			$(PARS_DIR)/utils.c

EXEC = $(EXEC_DIR)/exec_builtins.c $(EXEC_DIR)/exec_start.c $(EXEC_DIR)/path.c $(EXEC_DIR)/first_pipe.c \
		$(EXEC_DIR)/last_pipe.c $(EXEC_DIR)/exec_utils.c $(EXEC_DIR)/one_cmd.c $(EXEC_DIR)/inter_pipe.c \
		$(EXEC_DIR)/check_heredoc.c $(EXEC_DIR)/redir.c $(EXEC_DIR)/check_redir.c $(EXEC_DIR)/signals.c

#UTILS = $(UTILS_DIR)/init_struct.c $(UTILS_DIR)/divers.c $(UTILS_DIR)/free.c $(UTILS_DIR)/init_cmd.c
#REDIR = $(REDIR_DIR)/redir_one_cmd.c
#HEREDOC = $(HEREDOC_DIR)/check_heredoc.c

SRCS = $(FREE) $(PARSING) $(BUITLINS) $(EXEC) main.c
#SRCS = $(EXEC) $(BUITLINS) $(UTILS) $(REDIR) $(HEREDOC) main.c
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