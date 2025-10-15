/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:03:39 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 18:13:35 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_cmd(t_cmd **cmds, t_token *tokens, int *i)
{
	t_cmd	*current;

	(*i) = 0;
	current = malloc(sizeof(t_cmd));
	if (!current)
		return (error_malloc(), NULL);
	ft_bzero(current, sizeof(t_cmd));
	add_cmds(cmds, current);
	current->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
	if (!current->args)
		return (error_malloc(), NULL);
	current->next = NULL;
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

int	new_args(t_cmd *cmd, t_token *tmp, int i)
{
	cmd->args[i] = ft_strdup(tmp->value);
	if (!cmd->args[i])
		return (free_split(cmd->args), -1);
	return (1);
}

int	if_word(int *i, t_token *tmp, t_cmd *current)
{
	if (type(tmp) == 1)
	{
		if (new_args(current, tmp, *i) == -1)
			return (0);
		(*i)++;
	}
	return (1);
}

int	cmd_list(t_token *tokens, t_cmd **cmds, int i)
{
	t_token	*tmp;
	t_cmd	*current;
	t_token	*start;

	tmp = tokens;
	while (tmp)
	{
		current = create_cmd(cmds, tmp, &i);
		if (!current)
			return (0);
		start = tmp;
		while (tmp && tmp->type != PIPE)
		{
			if (!if_word(&i, tmp, current))
				return (0);
			tmp = tmp->next;
		}
		current->args[i] = NULL;
		current->redirect = redirections(current, start);
		if (next(tmp, current) == 1)
			tmp = tmp->next;
	}
	return (1);
}
