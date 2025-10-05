/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/05 22:07:10 by ocviller         ###   ########.fr       */
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
