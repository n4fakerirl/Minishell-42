/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:21:07 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/08 02:21:37 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_quote_state	find_quotes(t_token *token)
{
	int	len;

	if (!token || !token->value)
		return (NO_QUOTE);
	len = ft_strlen(token->value);
	if (len == 0)
		return (NO_QUOTE);
	if (token->value[0] == '\"' && token->value[len - 1] == '\"')
		return (DOUBLE_QUOTE);
	else if (token->value[0] == '\'' && token->value[len - 1] == '\'')
		return (SINGLE_QUOTE);
	else
		return (NO_QUOTE);
}

void	quoting(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value)
			tmp->state = find_quotes(tmp);
		tmp = tmp->next;
	}
}
