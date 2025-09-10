/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:28 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 20:42:02 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_cmd **cmds)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd)); // Initialise la structure à zéro
	if (!*cmds)
	{
		*cmds = cmd;
	}
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	cmd->next = NULL;
	return (cmd);
}

void	create_cmd(t_token *tokens, t_cmd *cmds)
{
	t_token	*tmp;
	int		i;

	cmds->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
	i = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			cmds->is_pipe = true;
			break ;
		}
		cmds->args[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
}

void	cmd_list(t_token *tokens, t_cmd **cmds)
{
	t_token *tmp = tokens;
	t_cmd *current = NULL;
	int i;

	while (tmp)
	{
		current = malloc(sizeof(t_cmd));
		if (!current)
			return ;
		add_cmds(cmds, current);
		current->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
		if (!current->args)
			return ;
		i = 0;
		while (tmp && tmp->type != PIPE)
		{
			current->args[i++] = ft_strdup(tmp->value);
			tmp = tmp->next;
		}
		current->args[i] = NULL;
		if (tmp && tmp->type == PIPE)
		{
			current->is_pipe = true;
			tmp = tmp->next;
		}
	}
}
