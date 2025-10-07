/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:32:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 19:40:16 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect(char *input, t_token **tokens)
{
	if (input[0] == '|')
		return (ft_lstadd_back_new(tokens, create_token(PIPE, ft_strdup("|"))), 1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDL,
					ft_strdup("<<"))), 2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDR,
					ft_strdup(">>"))), 2);
	if (input[0] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRL, ft_strdup("<"))), 1);
	if (input[0] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRR, ft_strdup(">"))), 1);
	return (0);
}

int	check_match(char *input, int singleq, int doubleq)
{
	int i;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			if (doubleq == 0)
				doubleq++;
			else
				doubleq--;
		}
		else if (input[i] == '\'')
		{
			if (singleq == 0)
				singleq++;
			else
				singleq--;
		}
		i++;
	}
	if ((singleq + doubleq) != 0)
		return (printf("minishell: error quote unmatched\n"), 0);
	return (1);
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	int y;
	i = 0;
	tokens = NULL;
	if (!check_match(input, 0, 0))
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += redirect(input + i, &tokens);
		else
		{
			y = 0;
			while (input[i + y] && !is_special_char(input[i + y]) && !ft_isspace(input[i + y]))
				y++;
			if (y > 0)
				ft_lstadd_back_new(&tokens, create_token(WORD, ft_substr(input, i,
						y)));
			i += y;
		}
	}
	return (tokens);
}

t_quote_state find_quotes(t_token *token)
{
	int len;

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

void quoting(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value)
			tmp->state = find_quotes(tmp);
		tmp = tmp->next;
	}
}
