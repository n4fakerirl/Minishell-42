/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:03:39 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/10 12:42:47 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_cmd	*create_cmd(t_cmd **cmds, t_token *tokens)
{
	t_cmd	*current;

	current = malloc(sizeof(t_cmd));
	if (!current)
		return (NULL);
	ft_bzero(current, sizeof(t_cmd));
	add_cmds(cmds, current);
	current->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
	if (!current->args)
		return (NULL);
	return (current);
}

int	next(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
	{
		cmd->is_pipe = true;
		return (1);
	}
	return (0);
}

int	type(t_token *tmp)
{
	if (tmp->type == WORD && tmp->value != NULL && tmp->value[0] != '\0')
		return (1);
	else
		return (0);
}

void	cmd_list(t_token *tokens, t_cmd **cmds, int i)
{
	t_token	*tmp;
	t_cmd	*current;
	t_token	*start;

	tmp = tokens;
	current = NULL;
	while (tmp)
	{
		current = create_cmd(cmds, tokens);
		i = 0;
		start = tmp;
		while (tmp && tmp->type != PIPE)
		{
			if (type(tmp) == 1)
			{
				current->args[i] = del_back(tmp, 0, 0);
				i++;
			}
			tmp = tmp->next;
		}
		current->args[i] = NULL;
		current->redirect = redirections(current, start);
		if (next(tmp, current) == 1)
		{
			free(current);
			tmp = tmp->next;
		}
	}
	free(tmp);
}
