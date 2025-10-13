/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:50 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/13 11:57:28 by ocviller         ###   ########.fr       */
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

t_env	*env_conv(char *str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (equal)
	{
		node->key = ft_substr(str, 0, equal - str);
		if (!node->key)
			return (free(node), NULL);
		node->value = ft_strdup(equal + 1);
		if (!node->value)
			return (free(node), NULL);
	}
	else
	{
		node->key = ft_strdup(str);
		if (!node->key)
			return (free(node), NULL);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*new;
	int		i;

	head = NULL;
	i = -1;
	if (!envp || !*envp)
		return (NULL);
	while (envp[++i])
	{
		new = env_conv(envp[i]);
		if (!head)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (head);
}
