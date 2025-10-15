/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:17:24 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 18:07:47 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialise(int *i, long long *res, int *sign, int *digit)
{
	*i = -1;
	*res = 0;
	*sign = 1;
	*digit = 0;
}

long	ft_atol(char *str, int *limit)
{
	int			i;
	long long	res;
	int			sign;
	int			digit;

	initialise(&i, &res, &sign, &digit);
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - 48;
		if (sign == 1 && (res > (LONG_MAX - digit) / 10))
			return (*limit = -1, -1);
		if (sign == -1 && (-res < (LONG_MIN + digit) / 10))
			return (*limit = -1, -1);
		res = res * 10 + digit;
		i++;
	}
	return (res * sign);
}

char	**dup_split(char **src)
{
	char	**result;
	int		i;

	i = 0;
	while (src[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (error_malloc(), NULL);
	i = 0;
	while (src[i])
	{
		result[i] = ft_strdup(src[i]);
		if (!result[i])
			return (free_split(result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
