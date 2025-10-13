/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/13 19:12:38 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_dollar_expand(char *str, t_expand *exp)
{
	int	y;

	if (ft_strncmp(str, "$?", 2) == 0)
	{
		expand_code(exp);
		if (!exp->result)
			return (exp->ret = -1, -1);
		return (2);
	}
	else
	{
		y = get_var_len(str);
		exp->result = expand_var(str, exp, y);
		if (!exp->result)
			return (exp->ret = -1, -1);
		return (y);
	}
}

int	exp_char(char *str, int i, t_expand *exp)
{
	int	y;

	if (str[i] == '$' && ((i == 0 || str[i - 1] != '\\') && str[i + 1]
			&& exp->q != '\''))
	{
		y = handle_dollar_expand(str + i, exp);
		if (y == -1)
			return (exp->ret = -1, -1);
		i += y;
	}
	else
	{
		exp->result = joinchar(exp->result, str[i]);
		if (!exp->result)
			return (exp->ret = -1, -1);
		i++;
	}
	return (i);
}

void	init_exp(t_expand *exp, int exit_status, t_env *env)
{
	exp->exit_status = exit_status;
	exp->env = env;
	exp->result = ft_strdup("");
	exp->q = 0;
	exp->ret = 0;
}

char	*expand_word(char *str, t_env *env, int exit_status, int i)
{
	t_expand	*exp;
	char		*result;

	exp = malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	init_exp(exp, exit_status, env);
	if (!exp->result || !exp->env)
		return (free_exp(exp), NULL);
	while (str[i])
	{
		if (handle_quote_expand(str, &i, exp) == -1)
			return (free_exp(exp), NULL);
		if (handle_quote_expand(str, &i, exp) == -1)
			continue ;
		if (!str[i])
			break ;
		i = exp_char(str, i, exp);
		if (exp->ret == -1)
			return (free_exp(exp), NULL);
	}
	result = ft_strdup(exp->result);
	free_exp(exp);
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
