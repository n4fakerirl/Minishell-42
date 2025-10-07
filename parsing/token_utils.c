/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:08:52 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 18:45:17 by ocviller         ###   ########.fr       */
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
