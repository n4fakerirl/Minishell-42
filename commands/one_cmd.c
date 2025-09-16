/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/16 12:27:26 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_command(t_pipex *pipex, t_cmd *cmd, int ac, char **envp)
{
	//Cas avec redirection
	if (cmd->redirect != 0)
		printf("Cas avec redirection\n");
	else
	{
		pipex->cmd_args
	}
}