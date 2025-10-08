/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 17:17:26 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_back(t_token *token, int i, int j)
{
	int		len;
	char	*buf;

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

void	trim_word(t_token *tokens)
{
	t_token	*tmp;
	char	*new_value;
	int		len;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->type == WORD || tmp->type == ARGREDIR)
			&& tmp->need_exp == false)
		{
			len = ft_strlen(tmp->value);
			new_value = strip_quotes(tmp->value, len, 0, 0);
			free(tmp->value);
			tmp->value = new_value;
		}
		if ((tmp->type == WORD || tmp->type == ARGREDIR) && ft_strchr(tmp->value, '\\'))
			tmp->value = del_back(tmp, 0, 0);
		tmp = tmp->next;
	}
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
