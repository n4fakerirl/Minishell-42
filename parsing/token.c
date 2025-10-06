/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:32:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/06 20:38:24 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect(char *input, t_token **tokens)
{
	if (input[0] == '|')
		return (ft_lstadd_back_new(tokens, create_token(PIPE, ft_strdup("|"),
					0)), 1);
	if (input[0] == '<' && input[1] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDL,
					ft_strdup("<<"), 0)), 2);
	if (input[0] == '>' && input[1] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRDR,
					ft_strdup(">>"), 0)), 2);
	if (input[0] == '<')
		return (ft_lstadd_back_new(tokens, create_token(REDIRL, ft_strdup("<"),
					0)), 1);
	if (input[0] == '>')
		return (ft_lstadd_back_new(tokens, create_token(REDIRR, ft_strdup(">"),
					0)), 1);
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

char	*trim_q(char *str, char c)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*new_cut(char *input, int i)
{
	char	*str;
	char	*tmp;

	str = ft_substr(input, 0, i);
	tmp = ft_strdup(str);
	free(str);
	str = trim_q(tmp, '\'');
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
	str = trim_q(tmp, '\"');
	free(tmp);
	return (str);
}

int	quotes_d(char *input, t_token **tokens, int i, char *tmp)
{
	i++;
	while (input[i] && input[i] != '\"')
		i++;
	if (input[i + 1] != '\0' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
	{
		while (input[i] == '\'' || input[i] == '\"')
			i++;
		while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' && input[i + 1] != '\"')
			i++;
		while (!ft_isspace(input[i]))
			i++;
		tmp = new_cut(input, i);
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, tmp, DOUBLE_QUOTE));
	}
	else
	{
		while (input[i] && !ft_isspace(input[i]))
			i++;
		i++;
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0,
						i), DOUBLE_QUOTE));
	}
	return (i);
}

int	quotes_s(char *input, t_token **tokens, int i, char *tmp)
{
	i++;
	while (input[i] && input[i] != '\'')
		i++;
	if (input[i + 1] != '\0' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
	{
		while (input[i] == '\'' || input[i] == '\"')
			i++;
		while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' && input[i + 1] != '\"')
			i++;
		while (!ft_isspace(input[i]))
			i++;
		tmp = new_cut(input, i);
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, tmp, SINGLE_QUOTE));
	}
	else
	{
		i++;
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0,
						i), SINGLE_QUOTE));
	}
	return (i);
}

int	wording(char *input, t_token **tokens)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup("");
	i = 0;
	if (input[i] == '\"')
		i += quotes_d(input, tokens, i, tmp);
	else if (input[i] == '\'')
		i += quotes_s(input, tokens, i, tmp);
	else
	{
		while (input[i] && !is_special_char(input[i]) && !ft_isspace(input[i]))
			i++;
		if (i > 0)
			ft_lstadd_back_new(tokens, create_token(WORD, ft_substr(input, 0,
						i), NO_QUOTE));
	}
	return (i);
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;

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
			i += wording(input + i, &tokens);
	}
	return (tokens);
}

int	find_allq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

void	del_quotes(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i] && tmp->value[i] != '\"' && tmp->value[i] != '\'')
			i++;
		if (find_allq(tmp->value + i) == 1)
			tmp->value[i] = '\0';
		tmp = tmp->next;
	}
}
