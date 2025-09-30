/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:31:17 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/27 11:16:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	ft_atol(char *str, int *limit)
{
	int			i;
	long long	res;
	int			sign;
	int			digit;

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

char	**dup_split(char **src)
{
	char	**result;
	int		i;

	i = 0;
	while (src[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
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

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	t_redir	*tmp;
	
	k = 0;
	j = 0;
	while (cmd)
	{
		tmp = cmd->redirect;
		i = 0;
		while (cmd->args[i])
		{
			fprintf(stderr, "CMD ARGS [%d]: %s\n", j, cmd->args[i]);
			i++;
		}
		while (tmp)
		{
			fprintf(stderr, "TYPE [%d]: %d\n", k, tmp->type);
			k++;
			tmp = tmp->next;
		}
		j++;
		cmd = cmd->next;
	}
}

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;	
	}
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
