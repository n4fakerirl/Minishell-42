/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:12:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 22:36:53 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_close(t_shell *shell)
{
	dup2(shell->pipe_infos->pipe_fd[0][1], 1);
	close(shell->pipe_infos->pipe_fd[0][1]);
	close(shell->pipe_infos->pipe_fd[0][0]);
	return ;
}

void	last_close(t_shell *shell, int i)
{
	dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	close(shell->pipe_infos->pipe_fd[i - 1][1]);
	return ;
}

void	inter_close(t_shell *shell, int i)
{
	dup2(shell->pipe_infos->pipe_fd[i][1], 1);
	dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
	close(shell->pipe_infos->pipe_fd[i][0]);
	close(shell->pipe_infos->pipe_fd[i][1]);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	return ;
}

void	redir(t_shell *shell, int i)
{
	if (i == 0)
		return (first_close(shell));
	else if (i == shell->nbr_cmd - 1)
		return (last_close(shell, i));
	else
		return (inter_close(shell, i));
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
