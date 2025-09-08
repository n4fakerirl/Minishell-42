/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:54:09 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 18:00:05 by ocviller         ###   ########.fr       */
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
		return (ft_lstadd_back(tokens, create_token(TOKEN_PIPE,
					ft_strdup("|"))), 1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back(tokens, create_token(TOKEN_HEREDOC,
					ft_strdup("<<"))), 2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back(tokens, create_token(TOKEN_REDIRECT_APPEND,
				ft_strdup(">>"))), 2);
	if (input[0] == '<')
		return (ft_lstadd_back(tokens, create_token(TOKEN_REDIRECT_IN,
				ft_strdup("<"))), 1);
	if (input[0] == '>')
		return (ft_lstadd_back(tokens, create_token(TOKEN_REDIRECT_OUT,
				ft_strdup(">"))), 1);
	return (0);
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;
	int		y;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += redirect(input + i, &tokens);
		else
		{
			y = i;
			while (input[y] && !is_special_char(input[y]) && !ft_isspace(input[y]))
				y++;
			if (y > i)
				ft_lstadd_back(&tokens, create_token(TOKEN_WORD, ft_substr(input,
							i, y - i)));
			i = y;
		}
		i++;
	}
	return (tokens);
}

t_token *new_type(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIRECT_APPEND || tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT)
		{
			if (tmp->next->type == TOKEN_WORD)
				tmp->next->type = TOKEN_EOF;
		}
		tmp = tmp->next;
	}
	return (tokens);
}
