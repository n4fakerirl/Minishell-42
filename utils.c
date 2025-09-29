/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:17:24 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/29 14:30:23 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_token **toklist, t_token *token)
{
	t_token	*tmp;

	tmp = *toklist;
	if (!*toklist)
	{
		*toklist = token;
		token->prev = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	token->prev = tmp;
}

void	add_cmds(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
	cmd->next = NULL;
}

int	lstlen(t_token **toklist)
{
	t_token	*tmp;
	int		i;

	tmp = *toklist;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	trim_words(t_token *tokens)
{
	t_token	*tmp;
	char	*new_value;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->state == DOUBLE_QUOTE)
		{
			new_value = ft_strtrim(tmp->value, "\"");
			free(tmp->value);
			tmp->value = new_value;
		}
		tmp = tmp->next;
	}
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
