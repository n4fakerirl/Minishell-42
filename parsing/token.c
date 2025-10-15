/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:32:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 19:31:51 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_match(char *input, int singleq, int doubleq)
{
	int	i;

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
		return (ft_putstr_fd("minishell: error quote unmatched\n", 2), 0);
	return (1);
}

int	skip_redir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (0);
	else if (ft_isspace(c))
		return (0);
	else
		return (1);
}

int	handle_word(char *input, t_token **tokens, int i)
{
	char	quote;

	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && !quote)
		{
			quote = input[i];
			i++;
			continue ;
		}
		if (input[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		if (!quote && (ft_isspace(input[i]) || is_special_char(input[i])))
			break ;
		i++;
	}
	if (i > 0)
		return (create_word(input, tokens, i));
	return (i);
}

t_token	*tokenize(char *input)
{
	int		i;
	int		count;
	t_token	*tokens;

	i = 0;
	count = 0;
	tokens = NULL;
	if (!check_match(input, 0, 0))
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			count = redirect(input + i, &tokens);
		else
			count = handle_word(input + i, &tokens, 0);
		if (count == -1)
			return (NULL);
		else
			i += count;
	}
	return (tokens);
}
