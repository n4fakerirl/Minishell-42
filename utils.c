/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:17:24 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/12 14:15:16 by ocviller         ###   ########.fr       */
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

void trim_words(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			tmp->value = ft_strtrim(tmp->value, "\"");
		tmp = tmp->next;
	}
}
