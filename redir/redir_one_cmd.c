/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:12:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/23 20:18:33 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redir(t_cmd *cmd)
{
	int	fd = 0;

	if (cmd->redirect->type == REDIRR || cmd->redirect->type == REDIRDR)
	{
		printf("TYPE : %d\n", cmd->redirect->type);
		printf("NAME OF FILE : %s\n", cmd->redirect->file);
		if (cmd->redirect->type == REDIRR)
			fd = open(cmd->redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redirect->type == REDIRDR)
			fd = open(cmd->redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);			
		printf("NUMERO DE FD : %d\n", fd);
		if (fd < 0)
		{
			perror("");
			return ;
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (cmd->redirect->type == REDIRDL)
	{
		fd = open(cmd->redirect->file, O_RDONLY);	
		if (fd < 0)
		{
			perror("");
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}
