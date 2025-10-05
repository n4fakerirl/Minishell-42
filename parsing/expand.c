/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/05 15:46:56 by ocviller         ###   ########.fr       */
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
				if (tmp->value[i] == '$')
				{
					if (i > 0 && tmp->value[i - 1] == '\\')
						tmp->need_exp = false;
					else if (tmp->value[i + 1] == '\0' || !ft_isalnum(tmp->value[i + 1]))
						tmp->need_exp = false;
					else
						tmp->need_exp = true;
				}
				i++;
			}
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

char *expand_simple_var(char *str, t_env *env, int exit_status)
{
    int i = 0;
    int y = 0;
    char *result = ft_strdup("");
    char *test;
    char *tmp;
    
    while (str[i])
    {
        if (str[i] == '$' && (i == 0 || str[i - 1] != '\\'))
        {
            if (str[i + 1] != '\0' && str[i + 1] == '?')
            {
                tmp = ft_itoa(exit_status);
                test = ft_strjoin(result, tmp);
                free(result);
                free(tmp);
                result = test;
                i += 2;
                continue;
            }
            y = 1;
            while (str[i + y] && ft_isalnum(str[i + y]))
                y++;
            test = ft_substr(str, i + 1, y - 1);
            char *value = get_var_value(test, env);
            free(test);
            tmp = ft_strjoin(result, value);
            free(result);
            result = tmp;
            i += y;
        }
        else
        {
            test = joinchar(result, str[i]);
            free(result);
            result = test;
            i++;
        }
    }
    return (result);
}

char	*expand(t_token *token, t_env *env, int exit_status)
{
	if (!token || !token->value || !token->need_exp)
		return (ft_strdup(token->value));
	return (expand_simple_var(token->value, env, exit_status));
}
