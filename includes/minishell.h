/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:00:55 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 10:49:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/includes/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Parsing
typedef struct s_cmd
{
	char			*name;
	char			**args;
}					t_cmd;

// Builtins
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;
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

// Utils
t_env				*init_env(char **envp);
long				ft_atol(char *str, int *limit);
int					ft_strcmp(const char *s1, const char *s2);
void				new_node(t_env **env, char *str);

// Exits
void				chdir_exit(char *message, char *path);
void				cwd_exit(char *message);
void				getpwd_exit(char *message);
void				exit_lit(char *message);
void				exit_num(char *message);

#endif