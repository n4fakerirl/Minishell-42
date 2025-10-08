/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 01:49:26 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_back(t_token *token, int i, int j)
{
	int		len;
	char	*buf;
	int		i;
	int		j;

	if (token->state == SINGLE_QUOTE)
		return (ft_strdup(token->value));
	len = ft_strlen(token->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (token->value[i])
	{
		if (token->value[i] == '\\')
		{
			i++;
			if (!token->value[i])
				break ;
			buf[j++] = token->value[i];
		}
		else
			buf[j++] = token->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

void trim_word(t_token *tokens)
{
    t_token *tmp;
    char    *new_value;
	int len;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == WORD || tmp->type == ARGREDIR)
        {
			len = ft_strlen(tmp->value);
            new_value = strip_quotes(tmp->value, len, 0, 0);
            free(tmp->value);
            tmp->value = new_value;
        }
        tmp = tmp->next;
    }
}
