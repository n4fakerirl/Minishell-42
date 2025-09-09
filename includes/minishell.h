/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:00:55 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/09 17:42:42 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

// Builtins
// Fonction ENV
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;
t_env	*init_env(char **envp);
void	print_list(t_env *env);
void	free_struct(t_env *env);
void	free_split(char **split);

//Fonction CD
int	ft_cd(char **split, t_env *env);

//Divers
int	ft_strcmp(const char *s1, const char *s2);

#endif