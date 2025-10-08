/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:08:52 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 02:22:29 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->state = NO_QUOTE;
	token->need_exp = false;
	return (token);
}

t_token	*new_type(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == REDIRDR || tmp->type == REDIRL || tmp->type == REDIRR)
		{
			if (tmp->next && tmp->next->type == WORD)
				tmp->next->type = ARGREDIR;
		}
		tmp = tmp->next;
	}
	return (tokens);
}

void	ft_lstadd_back_new(t_token **toklist, t_token *token)
{
	t_token	*tmp;

	tmp = *toklist;
	if (!token)
		return ;
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
