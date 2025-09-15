/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:41:43 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 14:11:56 by lenakach         ###   ########.fr       */
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

void	initialize(int *num1, int *lit1, long long *result, int *limit)
{
	*num1 = 0;
	*lit1 = 0;
	*result = 0;
	*limit = 0;
}

int	ft_exit(char **split, int *exit_flag)
{
	int			num1;
	int			lit1;
	int			i;
	long long	result;
	int			limit;

	i = 0;
	initialize(&num1, &lit1, &result, &limit);
	while (split[i])
		i++;
	printf("exit\n");
	if (i == 0)
		return (0);
	check_args(split[0], &num1, &lit1);
	if (lit1 == 1)
		return (exit_lit(split[0]), 2);
	if (i > 2)
		return (exit_num(split[0]), *exit_flag = 0, 1);
	result = ft_atol(split[0], &limit);
	if (limit == -1)
		return (exit_lit(split[0]), 2);
	return ((unsigned char)(result));
	return (1);
}
