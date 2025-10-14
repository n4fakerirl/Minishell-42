/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:20:23 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/14 16:12:03 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_noquote(t_token *t, int i, int j)
{
	int		len;
	char	*buf;

	len = ft_strlen(t->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (t->value[i])
	{
		if (t->value[i] == '\\' && t->value[i + 1] != '\0')
		{
			i++;
			if (!t->value[i])
				return (buf[j] = '\0', buf);
			buf[j++] = t->value[i];
		}
		else
			buf[j++] = t->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

char	*del_back(t_token *t, int i, int j)
{
	int		len;
	char	*buf;

	if (t->state == SINGLE_QUOTE)
		return (ft_strdup(t->value));
	len = ft_strlen(t->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (t->value[i])
	{
		if (t->value[i] == '\\' && backspecial(t->value[i + 1]))
		{
			i++;
			if (!t->value[i])
				return (buf[j] = '\0', buf);
			buf[j++] = t->value[i];
		}
		else
			buf[j++] = t->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

int	handle_back(t_token *tmp)
{
	char	*back;

	if (tmp->state == NO_QUOTE)
	{
		back = del_noquote(tmp, 0, 0);
		if (!back)
			return (0);
		free(tmp->value);
		tmp->value = ft_strdup(back);
		if (!tmp->value)
			return (0);
		free(back);
	}
	else
	{
		back = del_back(tmp, 0, 0);
		if (!back)
			return (0);
		free(tmp->value);
		tmp->value = ft_strdup(back);
		if (!tmp->value)
			return (0);
		free(back);
	}
	return (1);
}

int	handlexp(t_token *tmp)
{
	int		len;
	char	*new_value;

	len = ft_strlen(tmp->value);
	new_value = strip_quotes(tmp->value, len, 0, 0);
	if (!new_value)
		return (0);
	free(tmp->value);
	tmp->value = ft_strdup(new_value);
	if (!tmp->value)
		return (0);
	free(new_value);
	return (1);
}
