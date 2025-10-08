/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/08 01:51:33 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable(char *str)
{
	if (!str[1] || str[1] == ' ' || str[1] == '\'' || str[1] == '"')
		return (0);
	else if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	else if (ft_isalpha(str[1]) || str[1] == '_')
		return (1);
	else
		return (0);
}

void	need_expand(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	while (tmp)
	{
		i = 0;
		if (ft_strchr(tmp->value, '$'))
		{
			while (tmp->value[i] != '$')
				i++;
			if (is_expandable(tmp->value + i) == 1)
				tmp->need_exp = true;
			else
				tmp->need_exp = false;
		}
		tmp = tmp->next;
	}
}

char	*get_var_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*joinchar(const char *s1, char c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	res = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	res[j] = c;
	j++;
	res[j] = '\0';
	return (res);
}

char	*expand_code(int exit_status, char *result)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(exit_status);
	tmp = ft_strjoin(result, status);
	free(result);
	free(status);
	result = ft_strdup(tmp);
	free(tmp);
	return (result);
}

char	*expand_var(char *result, char *str, t_env *env, int y)
{
	char	*sub;
	char	*value;
	char	*tmp;

	sub = ft_substr(str, 1, y - 1);
	value = get_var_value(sub, env);
	free(sub);
	tmp = ft_strjoin(result, value);
	free(result);
	result = ft_strdup(tmp);
	return (result);
}

int	handle_quote_expand(char *str, int i, char *quote)
{
	if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
	{
		if (*quote == 0)
			*quote = str[i];
		else if (*quote == str[i])
			*quote = 0;
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

char	*expand_word(char *str, t_env *env, int exit_status)
{
	int		i;
	int		y;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (handle_quote_expand(str, i, &quote))
			i++;
		else if (str[i] == '$' && (i == 0 || str[i - 1] != '\\') && str[i
			+ 1] != '\0' && quote != '\'')
		{
			y = handle_dollar_expand(str + i, &result, env, exit_status);
			i += y;
		}
		else
			result = joinchar(result, str[i++]);
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_env *env, int exit_status)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->need_exp == true)
		{
			expanded = expand_word(tmp->value, env, exit_status);
			if (expanded)
			{
				free(tmp->value);
				tmp->value = ft_strdup(expanded);
				free(expanded);
			}
		}
		tmp = tmp->next;
	}
}
