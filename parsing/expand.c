/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/04 19:23:37 by ocviller         ###   ########.fr       */
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
				if (tmp->value[i - 1] != '\\' && tmp->value[i] == '$')
					tmp->need_exp = true;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

char	*joinword(int i, int y, char *var_name, char *envalue)
{
	char	*first;
	char	*last;
	char	*tmp;
	int		len;

	len = ft_strlen(var_name);
	first = NULL;
	last = NULL;
	first = ft_substr(var_name, 0, i);
	last = ft_substr(var_name, y, len - y);
	if (first && last)
	{
		tmp = ft_strjoin(first, envalue);
		free(first);
		first = ft_strjoin(tmp, last);
		return (ft_strdup(first));
	}
	else if (first && !last)
	{
		tmp = ft_strjoin(first, envalue);
		return (ft_strdup(tmp));
	}
	else if (!first && last)
	{
		tmp = ft_strjoin(envalue, last);
		return (ft_strdup(tmp));
	}
	return (ft_strdup(""));
}

char	*get_var_value(char *var_name, t_env *env)
{
	int		i;
	int		len;
	int		y;
	char	*tmp;
	char	*first;
	char	*last;

	i = 0;
	len = ft_strlen(var_name);
	y = len;
	while (var_name[i] != '$')
		i++;
	while (y > i + 1 && !skippable(var_name[y - 1]))
		y--;
	first = ft_substr(var_name, 0, i);
	last = ft_substr(var_name, y, len - y);
	tmp = ft_substr(var_name, i + 1, y - (i + 1));
	while (env)
	{
		if (env->key && ft_strcmp(env->key, tmp) == 0)
			return (joinword(i, y, var_name, env->value));
		env = env->next;
	}
	if (first && last)
		return (ft_strjoin(first, last));
	else if (!first && last)
		return (ft_strdup(last));
	else if (first && !last)
		return (ft_strdup(first));
	else
		return (ft_strdup(""));
}

char	*expand_simple_var(char *str, t_env *env, int exit_status)
{
	char	**split;
	int		i;
	char	*tmp;
	t_space	*space;

	space = NULL;
	split = ft_split_d(str, " $");
	i = -1;
	while (split[++i])
	{
		if (ft_strcmp(split[i], "$?") == 0)
			split[i] = ft_itoa(exit_status);
		else if (ft_strchr(split[i], '$'))
			split[i] = get_var_value(split[i], env);
	}
	space = create_sp(str, space);
	tmp = addspace(split, space);
	free(split);
	return (tmp);
}

char	*expand(t_token *token, t_env *env, int exit_status)
{
	if (!token || !token->value || !token->need_exp)
		return (ft_strdup(token->value));
	return (expand_simple_var(token->value, env, exit_status));
}
