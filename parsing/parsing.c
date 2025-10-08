/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:39:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 02:19:31 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	simple_redir(t_token *tmp)
{
	if ((!tmp->prev && !tmp->next))
		return (printr("newline"), 0);
	else if (tmp->prev && tmp->type == REDIRL && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printr("<"), 0);
	else if (tmp->prev && tmp->prev->type == REDIRL && tmp->type == REDIRR
		&& !tmp->next)
		return (printr("newline"), 0);
	else if (tmp->prev && tmp->type == REDIRR && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printr(">"), 0);
	else if (!tmp->next)
		return (printr("newline"), 0);
	return (1);
}

int	double_redir(t_token *tmp)
{
	if ((!tmp->prev && !tmp->next) || !tmp->next)
		return (printr("newline"), 0);
	else if (tmp->prev && tmp->type == REDIRDR && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printr(">>"), 0);
	else if (tmp->prev && tmp->type == REDIRDL && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printr("<<"), 0);
	return (1);
}

int	parse_args(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->prev || !tmp->next || !(tmp->prev->type == WORD
					|| tmp->prev->type == ARGREDIR))
				return (printr("|"), 0);
		}
		else if (tmp->type == REDIRR || tmp->type == REDIRL)
		{
			if (simple_redir(tmp) == 0)
				return (0);
		}
		else if (tmp->type == REDIRDR || tmp->type == REDIRDL)
		{
			if (double_redir(tmp) == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
