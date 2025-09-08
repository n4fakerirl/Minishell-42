/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:22 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/08 11:02:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Affiche le parametre donne

int	ft_echo(char **split)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (split[1] && !ft_strcmp(split[1], "-n"))
	{
		new_line = 0;
		i++;
	}
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
