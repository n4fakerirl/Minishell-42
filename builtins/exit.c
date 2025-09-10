/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:41:43 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/10 14:08:29 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	all_digit(char *str)
{
	int	i;
	
	i = 0;
	if (str[0] && str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

void	check_args(char *str, int *num, int *lit)
{
	if (all_digit(str))
	{
		*num = 1;
		*lit = 0;
		return ;
	}
	*num = 0;
	*lit = 1; 
}

int	ft_exit(char **split, int *exit_flag)
{
	int	num1;
	int	lit1;
	int	i;
	long long	result;
	int	limit;
	
	num1 = 0;
	lit1 = 0;
	result = 0;
	i = 0;
	limit = 0;
	while(split[i])
		i++;
	printf("exit\n");
	if (i == 1)
		return (0);
	check_args(split[1], &num1 , &lit1);
	if (i == 2)
	{
		if (lit1 == 1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(split[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		else
		{
			result = ft_atol(split[1], &limit);
			if (limit == -1)
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(split[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (2);
			}
			return((unsigned char)(result));
		}
	}
	if (lit1 == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(split[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);	
	}
	else if (num1 == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(split[1], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		*exit_flag = 0;
		return (1);
	}
	return (1);
}
