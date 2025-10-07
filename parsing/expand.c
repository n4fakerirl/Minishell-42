/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:23:53 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/07 19:49:03 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_expandable(char *str)
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
	int i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
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

char	*expand_word(char *str, t_env *env, int exit_status)
{
	int		i;
	int		y;
	char	*result;
	char	*test;
	char	*tmp;
	char	*value;

	i = 0;
	y = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || str[i - 1] != '\\') && str[i
			+ 1] != '\0')
		{
			if (str[i + 1] != '\0' && str[i + 1] == '?')
			{
				tmp = ft_itoa(exit_status);
				test = ft_strjoin(result, tmp);
				free(result);
				free(tmp);
				result = test;
				i += 2;
				continue ;
			}
			y = 1;
			while (str[i + y] && ft_isalnum(str[i + y]))
				y++;
			test = ft_substr(str, i + 1, y - 1);
			printf("test = %s\n", test);
			value = get_var_value(test, env);
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

void expand_tokens(t_token *tokens, t_env *env, int exit_status)
{
    t_token *tmp;
    char    *expanded;
    
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
