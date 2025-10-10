/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/10 14:15:00 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_back(t_token *t, int i, int j)
{
	int		len;
	char	*buf;

	if (t->state == SINGLE_QUOTE)
		return (ft_strdup(t->value));
	len = ft_strlen(t->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (t->value[i])
	{
		if (t->value[i] == '\\' && (t->value[i + 1] == '\\' 
			|| t->value[i + 1] == '"' || t->value[i + 1] == '\''))
		{
			i++;
			if (!t->value[i])
				return (buf[j] = '\0', buf);
			buf[j++] = t->value[i];
		}
		else
			buf[j++] = t->value[i];
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
			tmp->value = ft_strdup(new_value);
		}
		if ((tmp->type == WORD || tmp->type == ARGREDIR)
			&& ft_strchr(tmp->value, '\\'))
		{
			len = ft_strlen(tmp->value);
			new_value = del_back(tmp, 0, 0);
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
		}
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
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*joinchar(char *s1, char c)
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
	free(s1);
	return (res);
}
