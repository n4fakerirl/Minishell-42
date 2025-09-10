/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:56:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/10 20:23:42 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Affiche les variables d'environnement

void	print_list(t_env *env)
{
	while (env->next != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	printf("%s=%s\n", env->key, env->value);
}

t_env	*env_conv(char *str)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(str, '=');
	//printf("%s\n", equal);
	if (equal)
	{
		node->key = ft_substr(str, 0, equal - str);
		if (!node->key)
		{
			free_struct(node);
			return (NULL);
		}
		node->value = ft_strdup(equal + 1);
		if (!node->value)
		{
			free_struct(node);
			return (NULL);
		}
	}
	else
	{
		node->key = ft_strdup(str);
		if (!node->key)
		{
			free(node);
			return (NULL);
		}
		node->value = NULL;
	}
	//node->exported = 0;
	node->next = NULL;
	//free(equal);
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*new;
	int		i;

	head = NULL;
	tmp = NULL;
	new = NULL;
	i = 0;
	while (envp[i])
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
		i++;
	}
	return (head);
}
