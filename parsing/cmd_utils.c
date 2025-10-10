/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:25:54 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/10 17:03:42 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir(t_redir **redirs, t_redir *node)
{
	t_redir	*tmp;

	tmp = *redirs;
	if (!*redirs)
	{
		*redirs = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

t_redir	*redirections(t_cmd *cmd, t_token *token)
{
	t_redir	*node;
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= 2 && tmp->type <= 5)
		{
			if (tmp->next && tmp->next->type == ARGREDIR)
			{
				node = malloc(sizeof(t_redir));
				node->type = tmp->type;
				node->file = ft_strdup(tmp->next->value);
				if (!node->file)
					return (NULL);
				add_redir(&(cmd->redirect), node);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (cmd->redirect);
}
