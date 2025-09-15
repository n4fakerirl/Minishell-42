/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:22 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 13:45:29 by lenakach         ###   ########.fr       */
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
		printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
