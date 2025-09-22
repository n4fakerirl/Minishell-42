/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:00:55 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/22 17:26:00 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Structures

// Contient ma commande et mes arguments
typedef struct s_cmd
{
	char			**args;
	int				redirect;
	int				here_doc;
	struct s_cmd	*next;
}					t_cmd;

// Pour mes variables d'environnement
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_pipe
{
	int				nbr_pipes;
	int				pid[1024];
	int				pipe_fd[1024][2];
}					t_pipe;

typedef struct s_shell
{
	int				exit_status;
	int				nbr_cmd;
	char			*line;
	char			**av;
	char			**envp_initial;
	t_env			*env;
	t_cmd			*cmd;
	t_pipe			*pipe_infos;
}					t_shell;

// Builtins
int					exec_builtin(t_shell *shell, t_env **env);
int					is_builtin(char *cmd);
int					ft_cd(char **split, t_env **env);
int					ft_pwd(void);
int					ft_echo(char **split);
int					ft_exit(char **split, int *exit_flag);
int					ft_export(char **split, t_env **env, int *exit_code);
int					ft_unset(char **split, t_env **env);
t_env				*env_conv(char *str);
int					check_var(char *str);
int					check_node(char *str, t_env *env);
int					ft_env(char **split, t_env *env, bool egal);

// free
void				free_split(char **split);
void				free_cmd(t_cmd *cmd);
void				free_env(t_env *env);
void				free_shell(t_shell *shell);
void				free_move_cmd(t_cmd *cmd);

// Utils
t_env				*init_env(char **envp);
t_shell				*init_shell(char **envp);
t_cmd				*init_cmd(char **split);
long				ft_atol(char *str, int *limit);
int					ft_strcmp(const char *s1, const char *s2);
void				new_node(t_env **env, char *str);
char				**dup_split(char **src);
void				print_cmd(t_cmd *cmd);

// Exits
void				chdir_exit(char *message, char *path);
void				cwd_exit(char *message);
void				getpwd_exit(char *message);
void				exit_lit(char *message);
void				exit_num(char *message);

// Exec
void				start_exec(t_shell *shell, int i);
void				one_child(t_shell *shell, char **envp_initial);
void				one_cmd(t_shell *shell, char **envp_initial);
char				*get_cmd(t_shell *shell);
int					count_list(t_cmd *cmd);
void				first_child(t_shell *shell, char **envp_initial);
void				last_child(t_shell *shell, char **envp_initial, int i);
void				inter_child(t_shell *shell, char **envp_initial, int i);
void				fail_fork(t_shell *shell, int i);

#endif