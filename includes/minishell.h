/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:00:55 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/10 20:39:05 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/includes/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Builtins
typedef struct s_env
{
	char			*key;
	char			*value;
	//	int				exported;
	struct s_env	*next;
}					t_env;
t_env				*init_env(char **envp);
int					ft_cd(char **split, t_env *env);
int					ft_pwd(void);
int					ft_echo(char **split);
int					ft_env(char **split, t_env *env, bool egal);
int					ft_exit(char **split, int *exit_flag);
int					ft_export(char **split, t_env *env);
t_env				*env_conv(char *str);

// Divers
int					ft_strcmp(const char *s1, const char *s2);
void				print_list(t_env *env);

// free
void				free_struct(t_env *env);
void				free_split(char **split);

#endif