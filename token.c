/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:54:09 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 15:30:19 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token *));
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

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;
	int		y;

	i = 0;
	tokens = malloc(sizeof(t_token));
	printf("%s\n", input);
	while (input[i])
	{
		if (input[i] == '|')
			ft_lstadd_back(&tokens, create_token(TOKEN_PIPE, "|"));
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
				ft_lstadd_back(&tokens, create_token(TOKEN_HEREDOC, "<<"));
			else
				ft_lstadd_back(&tokens, create_token(TOKEN_REDIRECT_IN, "<"));
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				ft_lstadd_back(&tokens, create_token(TOKEN_REDIRECT_APPEND, ">>"));
			else
				ft_lstadd_back(&tokens, create_token(TOKEN_REDIRECT_OUT, ">"));
		}
		while (ft_isspace(input[i]))
			i++;
		y = i;
		while (!is_special_char(input[y]) && !ft_isspace(input[y]))
			y++;
		ft_lstadd_back(&tokens, create_token(TOKEN_WORD, ft_substr(input, i,
					y)));
		i += y;
	}
	return (tokens);
}
