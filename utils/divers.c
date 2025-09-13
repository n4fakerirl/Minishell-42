/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:31:17 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 16:32:50 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	ft_atol(char *str, int *limit)
{
	int		i;
	long long	res;
	int		sign;
	int	digit;

	i = 0;
	res = 0;
	sign = 1;
	digit = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
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
		{
			*limit = -1;
			return (-1);
		}
		if (sign == -1 && (-res < (LONG_MIN + digit) / 10))
		{
			*limit = -1;
			return (-1);
		}
		res = res * 10 + digit;
		i++;
	}
	return (res * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
