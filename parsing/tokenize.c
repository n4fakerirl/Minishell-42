/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:12:55 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/14 16:53:35 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect3(char *input, t_token **tokens)
{
	char	*tok;

	if (input[0] == '>')
	{
		tok = ft_strdup(">");
		if (!tok)
			return (-1);
		if (!ft_lstadd_back_new(tokens, create_token(REDIRR, tok)))
			return (-1);
		return (1);
	}
	return (0);
}

int	redirect2(char *input, t_token **tokens)
{
	char	*tok;

	if (input[0] == '>' && input[1] == '>')
	{
		tok = ft_strdup(">>");
		if (!tok)
			return (-1);
		if (!ft_lstadd_back_new(tokens, create_token(REDIRDR, tok)))
			return (-1);
		return (2);
	}
	if (input[0] == '<')
	{
		tok = ft_strdup("<");
		if (!tok)
			return (-1);
		if (!ft_lstadd_back_new(tokens, create_token(REDIRL, tok)))
			return (-1);
		return (1);
	}
	else
		return (redirect3(input, tokens));
}

int	redirect(char *input, t_token **tokens)
{
	char	*tok;

	if (input[0] == '|')
	{
		tok = ft_strdup("|");
		if (!tok)
			return (-1);
		if (!ft_lstadd_back_new(tokens, create_token(PIPE, tok)))
			return (-1);
		return (1);
	}
	if (input[0] == '<' && input[1] == '<')
	{
		tok = ft_strdup("<<");
		if (!tok)
			return (-1);
		if (!ft_lstadd_back_new(tokens, create_token(REDIRDL, tok)))
			return (-1);
		return (2);
	}
	else
		return (redirect2(input, tokens));
}

int	create_word(char *input, t_token **tokens, int i)
{
	char	*tok;

	tok = ft_substr(input, 0, i);
	if (!tok)
		return (-1);
	if (!ft_lstadd_back_new(tokens, create_token(WORD, tok)))
		return (-1);
	return (i);
}
