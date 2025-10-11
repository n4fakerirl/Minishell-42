/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 11:37:03 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	trim_word(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->type == WORD || tmp->type == ARGREDIR)
			&& tmp->need_exp == false)
		{
			if (!handlexp(tmp))
				return (0);
		}
		if ((tmp->type == WORD || tmp->type == ARGREDIR)
			&& ft_strchr(tmp->value, '\\'))
		{
			if (!handle_back(tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
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
