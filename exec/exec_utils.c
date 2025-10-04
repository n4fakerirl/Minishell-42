/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:35:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 18:17:58 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe++;	
		i++;
	}
	return (pipe);
}

int	count_list(t_cmd *cmd)
{
	int	i;

	i = 0;
	// if (!cmd || !cmd->args[0][0])
	// 	return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}