/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 02:24:30 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/10 11:30:51 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (result)
		free(result);
	if (value)
		free(value);
	result = ft_strdup(tmp);
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
			*result = joinchar(*result, str[i]);
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
