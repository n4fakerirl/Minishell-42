/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:50 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/11 14:32:14 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_env_new(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	if (key)
	{
		new->key = ft_strdup(key);
		if (!new->key)
			return (free(new), NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	return (new);
}

t_env	*ft_env_dup(t_env *env)
{
	t_env	*new_list;
	t_env	*tail;
	t_env	*tmp;

	new_list = NULL;
	tail = NULL;
	while (env)
	{
		tmp = ft_env_new(env->key, env->value);
		if (!tmp)
		{
			free_env(new_list);
			return (NULL);
		}
		if (!new_list)
			new_list = tmp;
		else
			tail->next = tmp;
		tail = tmp;
		env = env->next;
	}
	return (new_list);
}
