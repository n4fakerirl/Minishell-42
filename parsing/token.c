/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:32:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/05 03:21:04 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect(char *input, t_token **tokens)
{
	if (input[0] == '|')
		return (ft_lstadd_back_new(tokens, create_token(PIPE, ft_strdup("|"), 0)),
			1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDL, ft_strdup("<<"),
					0)), 2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDR, ft_strdup(">>"),
					0)), 2);
	if (input[0] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRL, ft_strdup("<"), 0)),
			1);
	if (input[0] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRR, ft_strdup(">"), 0)),
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


char *trim_q(char *str, char c)
{
	int trim = 0;
	int i = 0;
	int j = 0;
	int len = ft_strlen(str);
	
	while (str[i])
	{
		if ((i != 0 && i != (len - 1)) && str[i] == c)
			trim++;
		i++;
	}
	i -= trim;
	char *res = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		if (i > 0 && i < (len - 1) && str[i] != c)
		{
			res[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	res[j] = '\0';
	return (res);
}

int	wording(char *input, t_token **tokens)
{
	int	i;
	char *tmp = ft_strdup("");

	i = 0;
	if (input[i] == '\"')
	{
		i++;
		while (input[i] && input[i] != '\"')
			i++;
		if (input[i + 1] != '\0' && input[i + 1] == '\"')
		{
			while (input[i] == '\"')
				i++;
			while (input[i] && input[i] != '\"')
				i++;
			i++;
			tmp = ft_substr(input, 0, i);
			tmp = trim_q(tmp, '\"');																																													
			if (i > 0)
				ft_lstadd_back_new(tokens, create_token(WORD, tmp,
					DOUBLE_QUOTE));
		}
		else
		{
			i++;
			if (i > 0)
				ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0, i),
					DOUBLE_QUOTE));
		}
	}
	else if (input[i] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i + 1] != '\0' && input[i + 1] == '\'')
		{
			while (input[i] == '\'')
				i++;
			while (input[i] && input[i] != '\'')
				i++;
			i++;
			tmp = ft_substr(input, 0, i);
			tmp = trim_q(tmp, '\'');																																													
			if (i > 0)
				ft_lstadd_back_new(tokens, create_token(WORD, tmp,
					SINGLE_QUOTE));
		}
		else
		{
			i++;
			if (i > 0)
				ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0, i),
					SINGLE_QUOTE));
		}
	}
	else
	{
		while (input[i] && !is_special_char(input[i]) && !ft_isspace(input[i]))
			i++;
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0, i),
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

char *glue_words(char *value)
{
	int i = 0;
	int count = 0;
	while (value[i])
	{
		if (value[i + 1] != '\0' && value[i] == '\'' && value[i + 1] == '\'')
			count += 2;
		else if (value[i + 1] != '\0' && value[i] == '\"' && value[i + 1] == '\"')
			count += 2;
		i++;
	}
	i = i - count;
	char *res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	int y = 0;
	while (value[i])
	{
		if (value[i + 1] != '\0' && value[i] == '\'' && value[i + 1] == '\'')
			i += 2;
		else if (value[i + 1] != '\0' && value[i] == '\"' && value[i + 1] == '\"')
			i += 2;
		else
		{
			res[y] = value[i];
			i++;
			y++;
		}
	}
	res[y] = '\0';
	return (res);
}

int two_q(char *value)
{
	int i = 0;
	while (value[i])
	{
		if (value[i + 1] != '\0' && value[i] == '\'' && value[i + 1] == '\'')
			return (1);
		else if (value[i + 1] != '\0' && value[i] == '\"' && value[i + 1] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char *token_glue(char *value)
{
	if (two_q(value))
	{
		printf("TEST\n");
		value = glue_words(value);
	}
	return (value);
}
