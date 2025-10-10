/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/10 16:57:48 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_expand(char *str, char **result, t_env *env, int exit_status)
{
	int	y;

	if (ft_strncmp(str, "$?", 2) == 0)
	{
		*result = expand_code(exit_status, *result);
		return (2);
	}
	else
	{
		y = get_var_len(str);
		*result = expand_var(*result, str, env, y);
	}
	return (y);
}

int	is_possible(char prev, char next, char quote, int i)
{
	if ((i == 0 || prev != '\\') && next != '\0' && quote != '\'')
		return (1);
	else
		return (0);
}

char	*expand_word(char *str, t_env *env, int exit_status)
{
	int		i;
	int		y;
	char	q;
	char	*result;

	i = 0;
	q = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (handle_quote_expand(str, i, &q, &result))
			i++;
		else if (str[i] == '$' && ((i == 0 || str[i - 1] != '\\') && str[i
					+ 1] != '\0' && q != '\''))
		{
			y = handle_dollar_expand(str + i, &result, env, exit_status);
			i += y;
		}
		else
		{
			result = joinchar(result, str[i]);
			i++;
		}
	}
	return (result);
}

int	expand_tokens(t_token *tokens, t_env *env, int exit_status)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->need_exp == true)
		{
			expanded = expand_word(tmp->value, env, exit_status);
			if (!expanded)
				return (0);
			free(tmp->value);
			tmp->value = ft_strdup(expanded);
			if (!tmp->value)
				return (0);
			free(expanded);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
