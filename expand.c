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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/18 03:00:00 by ocviller         ###   ########.fr       */
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

int	backspecial(char c)
{
	if (c == '\\' || c == '"' || c == '$' || c == '\n')
		return (1);
	else
		return (0);
}

char	*del_back(t_token *token)
{
	int		len;
	char	*buf;
	int		i;
	int		j;

	j = 0;
	if (token->state == SINGLE_QUOTE)
		return (ft_strdup(token->value));
	len = ft_strlen(token->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\\')
		{
			i++;
			if (!token->value[i])
				break ;
			if (token->state == DOUBLE_QUOTE && backspecial(token->value[i]))
				buf[j++] = token->value[i];
			else
				buf[j++] = token->value[i];
		}
		else
			buf[j++] = token->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

int	skippable(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
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

	i = 0;
	len = ft_strlen(var_name);
	y = len;
	while (var_name[i] != '$')
		i++;
	while (y > i + 1 && !skippable(var_name[y - 1]))
		y--;
	tmp = ft_substr(var_name, i + 1, y - (i + 1));
	printf("---TMP %s---\n", tmp);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, tmp) == 0)
			return (joinword(i, y, var_name, env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*joinall(char **split)
{
	char	*tmp;
	char	*test;
	int		i;

	tmp = NULL;
	i = -1;
	while (split[++i])
	{
		if (!tmp)
			tmp = ft_strjoin(split[i], " ");
		else
		{
			test = ft_strjoin(tmp, split[i]);
			free(tmp);
			tmp = ft_strjoin(test, " ");
		}
	}
	i = ft_strlen(tmp);
	if (tmp[i - 1] == ' ')
		tmp[i - 1] = '\0';
	return (tmp);
}

char	*expand_simple_var(char *str, t_env *env)
{
	char	**split;
	int		i;
	char	*tmp;

	split = ft_split_d(str, " $");
	i = -1;
	while (split[++i])
	{
		if (ft_strchr(split[i], '$'))
			split[i] = get_var_value(split[i], env, str);
	}
	tmp = joinall(split);
	free(split);
	return (tmp);
}

char	*expand(t_token *token, t_env *env)
{
	if (!token || !token->value || !token->need_exp)
		return (ft_strdup(token->value));
	return (expand_simple_var(token->value, env));
}
