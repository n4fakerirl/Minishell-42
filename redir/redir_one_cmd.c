/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:12:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 16:33:05 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir(t_shell *shell, int i)
{
	if (i == 0)
	{
		fprintf(stdin, "Mon i == 0 dans redir\n");
		dup2(shell->pipe_infos->pipe_fd[0][1], 1);
		close(shell->pipe_infos->pipe_fd[0][1]);
		close(shell->pipe_infos->pipe_fd[0][0]);
		return ;
	}
	if (i == shell->nbr_cmd - 1)
	{
		fprintf(stderr, "REDIR DE MA [%d]eme commande\n", i);
		dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		close(shell->pipe_infos->pipe_fd[i - 1][1]);
		return ;
	}
	else
	{
		dup2(shell->pipe_infos->pipe_fd[i][1], 1);
		dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
		close(shell->pipe_infos->pipe_fd[i][0]);
		close(shell->pipe_infos->pipe_fd[i][1]);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		return ;
	}
}

void	open_fd(t_cmd *cmd)
{
	int	fd;

	while (cmd)
	{
		while (cmd->redirect)
		{
			if (cmd->redirect->type == REDIRR)
				fd = open(cmd->redirect->file, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else if (cmd->redirect->type == REDIRDR)
				fd = open(cmd->redirect->file, O_WRONLY | O_CREAT | O_APPEND,
						0644);	
			if (fd < 0)
			{
				perror("");
				return ;
			}
			cmd->redirect = cmd->redirect->next;
		}
		cmd = cmd->next;
	}
}

void	check_redir(t_shell *shell, int i)
{
	int	fd;

	fd = 0;
	if (shell->cmd->redirect == NULL && i != -1)
	{
		//fprintf(stderr, "JE N'AI PAS DE REDIR\n");
		//Redir de pipe si pas de redirections
		redir(shell, i);
		return ;
	}
	while (shell->cmd->redirect)
	{
		//fprintf(stderr, "J'AI UNE REDIR\n");
		if (shell->cmd->redirect->type == REDIRR || shell->cmd->redirect->type == REDIRDR)
		{
			//fprintf(stderr, "TYPE : %d\n", shell->cmd->redirect->type);
			//fprintf(stderr, "NAME OF FILE : %s\n", shell->cmd->redirect->file);
			if (shell->cmd->redirect->type == REDIRR)
				fd = open(shell->cmd->redirect->file, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else if (shell->cmd->redirect->type == REDIRDR)
				fd = open(shell->cmd->redirect->file, O_WRONLY | O_CREAT | O_APPEND,
						0644);
			//printf("NUMERO DE FD : %d\n", fd);
			if (fd < 0)
			{
				perror("");
				return ;
			}
			dup2(fd, 1);
			close(fd);
		}
		else if (shell->cmd->redirect->type == REDIRL)
		{
			fd = open(shell->cmd->redirect->file, O_RDONLY);
			if (fd < 0)
			{
				perror("");
				return ;
			}
			//fprintf(stderr, "REDIRL\n");
			dup2(fd, 0);
			close(fd);
		}
		shell->cmd->redirect = shell->cmd->redirect->next;
	}
	return ;
}
