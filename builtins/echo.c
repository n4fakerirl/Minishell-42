/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:22 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 17:38:42 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **split)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = 1;
	if (split[0] && !ft_strcmp(split[0], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (split[i] && !ft_strcmp(split[i], "-n"))
		i++;
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
