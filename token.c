/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:54:09 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 16:19:51 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
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
		return (ft_lstadd_back(tokens, create_token(PIPE, ft_strdup("|"))), 1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back(tokens, create_token(REDIRDL, ft_strdup("<<"))),
			2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back(tokens, create_token(REDIRDR, ft_strdup(">>"))),
			2);
	if (input[0] == '<')
		return (ft_lstadd_back(tokens, create_token(REDIRL, ft_strdup("<"))),
			1);
	if (input[0] == '>')
		return (ft_lstadd_back(tokens, create_token(REDIRR, ft_strdup(">"))),
			1);
	return (0);
}

int	wording(char *input, t_token **tokens)
{
	int	i;

	i = 0;
	if (input[i] == '"' || input[i] == '\'')
	{
		i++;
		while (input[i])
		{
			i++;
			if (input[i] == '"' || input[i] == '\'')
			{
				i++;
				return (ft_lstadd_back(tokens, create_token(WORD,
							ft_substr(input, 0, i))), i);
			}
		}
		if (i > 0)
			ft_lstadd_back(tokens, create_token(WORD, ft_substr(input, 0, i)));
	}
	else
	{
		while (input[i] && !is_special_char(input[i]) && !ft_isspace(input[i]))
			i++;
		if (i > 0)
			ft_lstadd_back(tokens, create_token(WORD, ft_substr(input, 0, i)));
	}
	return (i);
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
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
