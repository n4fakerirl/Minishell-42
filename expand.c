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
		if (tmp->type == WORD && (tmp->state == DOUBLE_QUOTE || tmp->state == NO_QUOTE))
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
	char	*str;

	i = 0;
	y = 0;
	while (token->value[i] != '\0' && token->value[i] != '$')
		i++;
	while (token->value[i + y] && token->value[i + y] != ' ' && token->value[i + y] != '\"')
		y++;
	str = ft_substr(token->value, i + 1, y);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, str) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
