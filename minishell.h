/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <include <ocviller@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:40:38 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 11:42:21 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,    // 0
	PIPE,    // 1
	REDIRL,  // < // 2
	REDIRR,  // > // 3
	REDIRDR, // >> // 4
	REDIRDL, // << // 5
	TEOF     // 6
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			need_exp;
	struct s_token	*next;
}					t_token;

t_token				*tokenize(char *input);
void				ft_lstadd_back(t_token **toklist, t_token *token);
t_token				*new_type(t_token *token);

#endif