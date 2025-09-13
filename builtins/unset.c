/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:47:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 20:08:45 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_var(char *str, t_env **env)
{
	t_env	*cur;
	t_env	*tmp;

	if (!env || !*env)
		return ;
	cur = *env;
	if (!ft_strcmp(str, cur->key))
	{
		*env = cur->next;
		return (free(cur->value), free(cur->key), free(cur));
	}
	while (cur->next)
	{
		if (!ft_strcmp(str, cur->next->key))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			return (free(tmp->key), free(tmp->value), free(tmp));
		}
		cur = cur->next;
	}
}

int	ft_unset(char **split, t_env **env)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i == 1)
		return (0);
	i = 0;
	while (split[++i])
	{
		if (check_var(split[i]))
			continue ;
		else if (!check_node(split[i], *env))
			continue ;
		else
			delete_var(split[i], env);
	}
	return (0);
}
