/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:24:30 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/15 19:15:48 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expandable(char *str)
{
	if (!str[1] || str[1] == ' ' || str[1] == '\'' || str[1] == '\"')
		return (0);
	else if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	else if (ft_isalpha(str[1]) || str[1] == '_')
		return (1);
	else
		return (0);
}

char	*expand_code(t_expand *exp)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(exp->exit_status);
	if (!status)
		return (NULL);
	tmp = ft_strjoin(exp->result, status);
	if (!tmp)
		return (NULL);
	free(exp->result);
	free(status);
	exp->result = ft_strdup(tmp);
	if (!exp->result)
		return (NULL);
	free(tmp);
	return (exp->result);
}

char	*expand_var(char *str, t_expand *exp, int y)
{
	char	*sub;
	char	*value;
	char	*tmp;

	sub = ft_substr(str, 1, y - 1);
	if (!sub)
		return (NULL);
	value = get_var_value(sub, exp->env);
	if (!value)
		return (NULL);
	free(sub);
	tmp = ft_strjoin(exp->result, value);
	if (!tmp)
		return (NULL);
	if (exp->result)
		free(exp->result);
	if (value)
		free(value);
	exp->result = ft_strdup(tmp);
	if (!exp->result)
		return (NULL);
	free(tmp);
	return (exp->result);
}

int	handle_quote_expand(char *str, int *i, t_expand *exp)
{
	if ((str[(*i)] == '\"' || str[(*i)] == '\'') && (*i == 0 || str[(*i
					- 1)] != '\\'))
	{
		if (exp->q == 0)
			exp->q = str[(*i)];
		else if (exp->q == str[(*i)])
			exp->q = 0;
		else
		{
			exp->result = joinchar(exp->result, str[(*i)]);
			if (!exp->result)
				return (exp->ret = -1, -1);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	get_var_len(char *str)
{
	int	y;

	y = 1;
	while (str[y] && skippable(str[y]))
		y++;
	return (y);
}
