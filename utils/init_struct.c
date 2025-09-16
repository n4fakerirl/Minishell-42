/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:56:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/16 14:28:47 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_node(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	new = env_conv(str);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
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
	tmp = NULL;
	new = NULL;
	i = -1;
	if (!envp || !envp)
			return NULL;
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

t_shell	*init_shell(char **envp)
{
	t_shell *new_shell;
	int	i;

	i = 0;
	new_shell = malloc(sizeof(t_shell));
	if (!new_shell)
		return (NULL);
	new_shell->exit_status = 0;
	new_shell->av = NULL;
	new_shell->env = init_env(envp);
	if (!new_shell->env)
		return (free_shell(new_shell), NULL);
	new_shell->cmd = NULL;
	return (new_shell);
}