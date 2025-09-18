/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:54:09 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/18 01:59:47 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value, t_quote_state state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->state = state;
	token->need_exp = false;
	return (token);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	redirect(char *input, t_token **tokens)
{
	if (input[0] == '|')
		return (ft_lstadd_back(tokens, create_token(PIPE, ft_strdup("|"), 0)),
			1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back(tokens, create_token(REDIRDL, ft_strdup("<<"),
					0)), 2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back(tokens, create_token(REDIRDR, ft_strdup(">>"),
					0)), 2);
	if (input[0] == '<')
		return (ft_lstadd_back(tokens, create_token(REDIRL, ft_strdup("<"), 0)),
			1);
	if (input[0] == '>')
		return (ft_lstadd_back(tokens, create_token(REDIRR, ft_strdup(">"), 0)),
			1);
	return (0);
}

int	check_match(char *input)
{
	int	doubleq;
	int	singleq;
	int	i;

	doubleq = 0;
	singleq = 0;
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

int	wording(char *input, t_token **tokens)
{
	int	i;

	i = 0;
	if (input[i] == '"')
	{
		while (input[i])
			i++;
		if (i > 0)
			ft_lstadd_back(tokens, create_token(WORD, ft_substr(input, 0, i),
					DOUBLE_QUOTE));
	}
	else if (input[i] == '\'')
	{
		while (input[i])
			i++;
		if (i > 0)
			ft_lstadd_back(tokens, create_token(WORD, ft_substr(input, 0, i),
					SINGLE_QUOTE));
	}
	else
	{
		while (input[i] && !is_special_char(input[i]) && !ft_isspace(input[i]))
			i++;
		if (i > 0)
			ft_lstadd_back(tokens, create_token(WORD, ft_substr(input, 0, i),
					NO_QUOTE));
	}
	return (i);
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	if (!check_match(input))
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += redirect(input + i, &tokens);
		else
			i += wording(input + i, &tokens);
	}
	return (tokens);
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
