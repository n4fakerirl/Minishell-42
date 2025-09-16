/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:00:55 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/16 13:43:41 by lenakach         ###   ########.fr       */
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
# include <unistd.h>

// Structures

// Contient ma commande et mes arguments
typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				redirect;
	int				here_doc;
}					t_cmd;

// Pour mes variables d'environnement
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	int				exit_status;
	char			**av;
	t_env			*env;
	t_cmd			*cmd;
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

// Utils
t_env				*init_env(char **envp);
t_shell				*init_shell(char **envp);
long				ft_atol(char *str, int *limit);
int					ft_strcmp(const char *s1, const char *s2);
void				new_node(t_env **env, char *str);
char				**dup_split(char **src);

// Exits
void				chdir_exit(char *message, char *path);
void				cwd_exit(char *message);
void				getpwd_exit(char *message);
void				exit_lit(char *message);
void				exit_num(char *message);

// Pipex
typedef struct s_pipex
{
	int				fd_infile;
	int				fd_outfile;
	int				pid[1024];
	int				pipou[1024][2];
	char			*path;
	char			**path_final;
	char			**cmd_args;
	char			*cmd;
	int				start;
	int				i;
	int				j;
}					t_pipex;

#endif