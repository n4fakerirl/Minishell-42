/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand->c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student->42->fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/18 01:39:57 by ocviller         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	need_expand(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->state == DOUBLE_QUOTE
				|| tmp->state == NO_QUOTE))
		{
			i = 0;
			while (tmp->value[i])
			{
				if (tmp->value[i] == '$')
					tmp->need_exp = true;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

char	*expand(t_token *token, t_env *env)
{
	int		i;
	int		y;
	char	*var;
	char	*first;
	int		len;
	char	*final;

	final = NULL;
	first = NULL;
	i = 0;
	y = 0;
	len = ft_strlen(token->value);
	while (token->value[i] != '\0' && token->value[i] != '$')
		i++;
	if (i > 0)
		first = ft_substr(token->value, 0, i);
	while (token->value[i + y] && token->value[i + y] != ' ' && token->value[i
		+ y] != '\"')
		y++;
	var = ft_substr(token->value, i + 1, y - 1);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, var) == 0)
		{
			if (first)
				first = ft_strjoin(first, env->value);
			else
				first = ft_strdup(env->value);
		}
		env = env->next;
	}
	if (token->value[i + y] != '\0')
		final = ft_substr(token->value, i + y, len - y - i);
	if (final)
	{
		first = ft_strjoin(first, final);
	}
	return (first);
}
