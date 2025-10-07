/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 20:14:04 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_back(t_token *token)
{
	int		len;
	char	*buf;
	int		i;
	int		j;

	j = 0;
	if (token->state == SINGLE_QUOTE)
		return (ft_strdup(token->value));
	len = ft_strlen(token->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\\')
		{
			i++;
			if (!token->value[i])
				break ;
			if (token->state == DOUBLE_QUOTE && backspecial(token->value[i]))
				buf[j++] = token->value[i];
			else
				buf[j++] = token->value[i];
		}
		else
			buf[j++] = token->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

int count_q(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char *trim_one(char *str)
{
	int i;
	int j;
	int len;
	char *dup;
	
	i = 0;
	j = 0;
	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		dup[j] = str[i];
		i++;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

void trim_word(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			tmp->value = strip_quotes(tmp->value, 0, 0, 0);
		tmp = tmp->next;
	}
}
