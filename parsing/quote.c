/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:21:07 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/10 16:51:42 by ocviller         ###   ########.fr       */
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

int	simple_quote(t_inquote *quote)
{
	if (!quote->in_single)
		quote->in_single = 1;
	else
		quote->in_single = 0;
	return (1);
}

int	double_quote(t_inquote *quote)
{
	if (!quote->in_double)
		quote->in_double = 1;
	else
		quote->in_double = 0;
	return (1);
}

char	*strip_quotes(char *str, int len, int i, int j)
{
	char		*result;
	t_inquote	quote;

	result = malloc(len + 1);
	quote.in_double = 0;
	quote.in_single = 0;
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !quote.in_double)
		{
			i += simple_quote(&quote);
			continue ;
		}
		if (str[i] == '\"' && !quote.in_single)
		{
			i += double_quote(&quote);
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
