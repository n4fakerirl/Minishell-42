# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 22:30:15 by ocviller          #+#    #+#              #
#    Updated: 2025/09/08 13:00:57 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Sources libft de base
SRC = ft_atoi.c ft_strncmp.c ft_strrchr.c ft_calloc.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_strjoin.c ft_putchar_fd.c ft_strtrim.c ft_strlen.c \
		ft_substr.c ft_strdup.c ft_itoa.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_isalpha.c ft_isdigit.c \
		ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_split.c ft_atol.c ft_isspace.c ft_strcmp.c

# Sources bonus libft
SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back1.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Sources ft_printf
SRC_PRINTF = ft_printf/ft_printf.c ft_printf/ft_printchar.c ft_printf/ft_printnb.c \
			ft_printf/ft_printstr.c ft_printf/ft_printuns.c ft_printf/ft_printhex.c \
			ft_printf/ft_printmem.c

# Sources get_next_line
SRC_GNL = get_next_line/get_next_line.c

# Objets correspondants
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ_PRINTF = $(SRC_PRINTF:.c=.o)
OBJ_GNL = $(SRC_GNL:.c=.o)

# Tous les objets
ALL_OBJ = $(OBJ) $(OBJ_PRINTF) $(OBJ_GNL)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ift_printf -Iget_next_line -Iminishell -fPIE

RM = rm -f

all: $(NAME)

$(NAME): $(ALL_OBJ)
	@ar rcs $(NAME) $(ALL_OBJ)
	@echo "$(NAME) created with ft_printf and get_next_line!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(ALL_OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(ALL_OBJ) $(OBJ_BONUS)
	@echo "$(NAME) with bonus, ft_printf and get_next_line created!"

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS) $(OBJ_PRINTF) $(OBJ_GNL)
	@echo "Objects removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re bonus