/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/11 12:34:00 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_expand(char *str, char **result, t_env *env, int exit_status)
{
	int	y;

	if (ft_strncmp(str, "$?", 2) == 0)
	{
		*result = expand_code(exit_status, *result);
		if (!*result)
			return (-1);
		return (2);
	}
	else
	{
		y = get_var_len(str);
		*result = expand_var(*result, str, env, y);
		if (!*result)
			return (-1);
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

int	addchar(char **result, char c, int *i)
{
	*result = joinchar(*result, c);
	if (!*result)
		return (-1);
	else
		(*i)++;
	return (1);
}

char	*expand_word(char *str, t_env *env, int exit_status, int i)
{
	int		y;
	char	q;
	char	*result;

	q = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (handle_quote_expand(str, &i, &q, &result) == -1)
			return (NULL);
		if (!str[i])
			break ;
		else if (str[i] == '$' && ((i == 0 || str[i - 1] != '\\') && str[i
					+ 1] != '\0' && q != '\''))
		{
			y = handle_dollar_expand(str + i, &result, env, exit_status);
			if (y == -1)
				return (NULL);
			i += y;
		}
		else
		{
			if (addchar(&result, str[i], &i) == -1)
				return (NULL);
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
			expanded = expand_word(tmp->value, env, exit_status, 0);
			if (!expanded)
				return (0);
			free(tmp->value);
			tmp->value = ft_strdup(expanded);
			if (!tmp->value)
				return (free(expanded), 0);
			free(expanded);
		}
		tmp = tmp->next;
	}
	return (1);
}
