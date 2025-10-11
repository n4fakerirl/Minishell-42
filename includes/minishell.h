/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:43 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 13:25:45 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies communes
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Librairies parsing
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>

// Libraries  exec
# include <errno.h>
# include <limits.h>
# include <sys/types.h>

extern volatile sig_atomic_t	g_signal;

// Structures
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRL,
	REDIRR,
	REDIRDR,
	REDIRDL,
	ARGREDIR
}								t_token_type;

typedef enum e_quote_state
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}								t_quote_state;

typedef struct s_inquote
{
	int							in_double;
	int							in_single;
}								t_inquote;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	bool						need_exp;
	t_quote_state				state;
	struct s_token				*prev;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**args;
	t_redir						*redirect;
	int							is_pipe;
	int							here_doc;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_pipe
{
	int							nbr_pipe;
	int							pid[1024];
	int							pipe_fd[1024][2];
}								t_pipe;

typedef struct s_shell
{
	int							exit_status;
	int							nbr_cmd;
	int							saved_stdin;
	int							saved_stdout;
	char						**envp_initial;
	int							heredoc_interrupted;
	t_env						*env;
	t_cmd						*cmd;
	t_pipe						*pipe_infos;
}								t_shell;

// PRINT A SUPP
void							print_cmd(t_cmd *cmd);
void							print_token(t_token *token);

// ETAPE 1 : PARSING
// 1.1 START PARSING
void							start_parsing(char *str, int exit_status,
									t_shell *shell);
t_shell							*init_shell(char **envp, int exit_status,
									int first, t_env *tmp_env);

t_env							*env_conv(char *str);
t_env							*init_env(char **envp);

// 1.2 TOKEN & TOKEN_UTILS
t_token							*tokenize(char *input);
t_token							*new_type(t_token *tokens);
t_token							*create_token(t_token_type type, char *value);
void							quoting(t_token *tokens);
int								create_word(char *input, t_token **tokens,
									int i);
int								redirect(char *input, t_token **tokens);

// 1.3 PARSE ARGS
int								parse_args(t_token *tokens);

// 1.4 EXPAND $ EXPAND UTILS
void							need_expand(t_token *tokens);
int								expand_tokens(t_token *tokens, t_env *env,
									int exit_status);
char							*expand_code(int exit_status, char *result);
char							*get_var_value(char *var_name, t_env *env);
char							*expand_var(char *result, char *str, t_env *env,
									int y);
int								handle_quote_expand(char *str, int *i,
									char *quote, char **result);
char							*joinchar(char *s1, char c);
int								get_var_len(char *str);
int								is_expandable(char *str);

// 1.5 TRIM WORDS
int								trim_word(t_token *tokens);
char							*strip_quotes(char *str, int len, int i, int j);
char							*del_back(t_token *token, int i, int j);
char							*del_noquote(t_token *t, int i, int j);

// UTILS
int								backspecial(char c);
int								is_special_char(char c);
int								ft_isspace(int c);
int								skippable(char c);
void							ft_lstadd_back_new(t_token **toklist,
									t_token *token);
int								lstlen(t_token **toklist);
void							printr(char *message);
int								handlexp(t_token *tmp);
int								handle_back(t_token *tmp);

// CMD
int								cmd_list(t_token *tokens, t_cmd **cmds, int i);
t_redir							*redirections(t_cmd *cmd, t_token *token);
void							add_cmds(t_cmd **cmds, t_cmd *cmd);

// Free
void							free_shell(t_shell *shell);
void							free_cmd(t_cmd *cmd);
void							free_redir(t_redir *redir);
void							free_split(char **split);
void							free_env(t_env *env);
void							free_token(t_token *token);

// Exec
void							start_exec(t_shell *shell);
void							one_cmd(t_shell *shell, char **envp_initial);
void							first_child(t_shell *shell,
									char **envp_initial);
void							inter_child(t_shell *shell,
									char **envp_initial);
void							last_child(t_shell *shell, char **envp_initial);
void							fail_fork(t_shell *shell, int i);
int								count_pipe(char *str);
int								count_list(t_cmd *cmd);
int								is_builtin(char *cmd);
int								exec_builtin(t_shell *shell, t_env **env);
char							*find_path(t_env *env);
char							*fill_path(char **path, char *cmd);
char							*get_cmd(t_shell *shell);
void							chdir_exit(char *message, char *path);
void							cwd_exit(char *message);
void							getpwd_exit(char *message);
void							exit_lit(char *message);
void							exit_num(char *message);
char							**dup_split(char **src);
long							ft_atol(char *str, int *limit);
void							new_node(t_env **env, char *str);
int								split_len(char **split);
int								ft_cd(char **split, t_env **env);
int								ft_pwd(void);
int								ft_echo(char **split);
int								ft_exit(char **split, int *exit_flag);
int								ft_export(char **split, t_env **env,
									int *exit_code);
int								ft_unset(char **split, t_env **env);
t_env							*env_conv(char *str);
int								check_var(char *str);
int								check_node(char *str, t_env *env);
int								ft_env(char **split, t_env *env, bool egal);
int								check_heredoc(t_shell *shell);
void							redir(t_shell *shell, int i);
void							open_fd(t_cmd *cmd);
void							check_redir(t_shell *shell, int i);
void							waiting(t_shell *shell);

void							sigint_handler(int sig);
void							check_signal_exec(t_shell *shell, int *status);
void							check_signal_heredoc(t_shell *shell,
									int *status);

t_env							*ft_env_new(const char *key, const char *value);
t_env							*ft_env_dup(t_env *env);

#endif
