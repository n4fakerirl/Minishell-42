/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:24:30 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/11 11:11:01 by ocviller         ###   ########.fr       */
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

char	*expand_code(int exit_status, char *result)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(exit_status);
	if (!status)
		return (NULL);
	tmp = ft_strjoin(result, status);
	if (!tmp)
		return (NULL);
	free(result);
	free(status);
	result = ft_strdup(tmp);
	if (!result)
		return (NULL);
	free(tmp);
	return (result);
}

char	*expand_var(char *result, char *str, t_env *env, int y)
{
	char	*sub;
	char	*value;
	char	*tmp;

	sub = ft_substr(str, 1, y - 1);
	if (!sub)
		return (NULL);
	value = get_var_value(sub, env);
	if (!value)
		return (NULL);
	free(sub);
	tmp = ft_strjoin(result, value);
	if (!tmp)
		return (NULL);
	if (result)
		free(result);
	if (value)
		free(value);
	result = ft_strdup(tmp);
	if (!result)
		return (NULL);
	free(tmp);
	return (result);
}

int	handle_quote_expand(char *str, int i, char *quote, char **result)
{
	if ((str[i] == '\"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
	{
		if (*quote == 0)
			*quote = str[i];
		else if (*quote == str[i])
			*quote = 0;
		else
		{
			*result = joinchar(*result, str[i]);
			if (!*result)
				return (-1);
		}
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
