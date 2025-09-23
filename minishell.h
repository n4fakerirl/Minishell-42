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
	ARGREDIR // 6
}					t_token_type;

typedef enum e_quote_state
{
	NO_QUOTE,     // 0
	SINGLE_QUOTE, // 1
	DOUBLE_QUOTE  // 2
}					t_quote_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			need_exp;
	t_quote_state	state;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	bool			is_pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	
}					t_shell;

t_token				*tokenize(char *input);
void				ft_lstadd_back(t_token **toklist, t_token *token);
t_token				*new_type(t_token *token);
t_env				*init_env(char **envp);
char				*expand(t_token *token, t_env *env);
int					lstlen(t_token **toklist);
void				cmd_list(t_token *tokens, t_cmd **cmds, t_env *env);
void				add_cmds(t_cmd **cmds, t_cmd *cmd);
void				trim_words(t_token *tokens);
void				need_expand(t_token *tokens);
int					parse_args(t_token *tokens);
char	*ft_triplejoin(char const *s1, char const *s2, char const *s3);

#endif