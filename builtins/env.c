/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:56:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/08 16:49:55 by lenakach         ###   ########.fr       */
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
	if (equal)
	{
		node->key = ft_substr(str, 0, equal - str);
		node->value = ft_strdup(equal + 1);
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*head = NULL;
	t_env	*tmp;
	t_env	*new;
	int		i;

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
	//print_list(head);
	return (head);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s", env->key, env->value);
		env = env->next;
	}
	return (0);
}
