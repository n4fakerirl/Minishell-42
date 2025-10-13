/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:22 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 15:25:13 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **split)
{
	int	new_line;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_line = 1;
	if (split[0] && !ft_strncmp(split[0], "-n", 2))
	{
		j = 2;
		while (split[0][j] && split[0][j] == 'n')
			j++;
		if (split[0][j] == '\0')
		{
			new_line = 0;
			i++;
		}
	}
	while (split[i] && !ft_strncmp(split[i], "-n", 2))
	{
		j = 2;
		while (split[i][j] && split[i][j] == 'n')
			j++;
		if (split[i][j] == '\0')
			i++;
		else
			break ;
	}
	while (split[i])
	{
		write(STDOUT_FILENO, split[i], ft_strlen(split[i]));
		if (split[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
