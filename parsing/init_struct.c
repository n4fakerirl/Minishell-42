/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:19:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 12:52:55 by ocviller         ###   ########.fr       */
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

t_pipe	*init_pipe(void)
{
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
		return (NULL);
	new_pipe->nbr_pipe = 0;
	return (new_pipe);
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

void init_shell(char **envp, int exit_status, t_shell *new_shell)
{
	new_shell->nbr_cmd = 0;
	new_shell->exit_status = exit_status;
	new_shell->saved_stdin = 0;
	new_shell->heredoc_interrupted = 0;
	new_shell->saved_stdout = 0;
	new_shell->cmd = NULL;
	new_shell->pipe_infos = init_pipe();
	//new_shell->env = init_env(envp);
	new_shell->envp_initial = dup_split(envp);
	if (!new_shell->envp_initial)
		return (free_shell(new_shell));
	if (!new_shell->env)
		return (free_shell(new_shell));
}
