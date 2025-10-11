/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:12:55 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/11 11:14:26 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect2(char *input, t_token **tokens)
{
	char	*tok;

    if (input[0] == '>' && input[1] == '>')
	{
		tok = ft_strdup(">>");
		if (!tok)
			return (-1);
		return (ft_lstadd_back_new(tokens, create_token(REDIRDR, tok)), 2);
	}
	if (input[0] == '<')
	{
		tok = ft_strdup("<");
		if (!tok)
			return (-1);
		return (ft_lstadd_back_new(tokens, create_token(REDIRL, tok)), 1);
	}
	if (input[0] == '>')
	{
		tok = ft_strdup(">");
		if (!tok)
			return (-1);
		return (ft_lstadd_back_new(tokens, create_token(REDIRR, tok)), 1);
	}
	return (0);
}

int	redirect(char *input, t_token **tokens)
{
	char	*tok;

	if (input[0] == '|')
	{
		tok = ft_strdup("|");
		if (!tok)
			return (-1);
		return (ft_lstadd_back_new(tokens, create_token(PIPE, tok)), 1);
	}
	if (input[0] == '<' && input[1] == '<')
	{
		tok = ft_strdup("<<");
		if (!tok)
			return (-1);
		return (ft_lstadd_back_new(tokens, create_token(REDIRDL, tok)), 2);
	}
	if (input[0] == '<' || input[0] == '>')
		return (redirect2(input, tokens));
	return (0);
}

int	create_word(char *input, t_token **tokens, int i)
{
	char	*tok;

	tok = ft_substr(input, 0, i);
	if (!tok)
		return (-1);
	ft_lstadd_back_new(tokens, create_token(WORD, tok));
	return (i);
}
