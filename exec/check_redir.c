/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:24:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 19:50:55 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_right(t_shell *shell)
{
	int	fd;

	fd = 0;
	if (shell->cmd->redirect->type == REDIRR)
		fd = open(shell->cmd->redirect->file, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (shell->cmd->redirect->type == REDIRDR)
		fd = open(shell->cmd->redirect->file, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (fd < 0)
		return (perror(""));
	dup2(fd, 1);
	close(fd);
}

int	redir_simple_left(t_shell *shell, int i)
{
	int	fd;

	fd = open(shell->cmd->redirect->file, O_RDONLY);
	if (fd < 0)
	{
		if (i == -1)
		{
			perror("");
			return (1);
		}
		else
		{
			perror("");
			free_exit(shell);
			close(fd);
			exit(1);
		}
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

void	redir_heredoc(t_shell *shell)
{
	int	fd;

	fd = shell->cmd->here_doc;
	if (fd < 0)
		return (perror(""));
	dup2(fd, 0);
	close(fd);
}

int	check_redir(t_shell *shell, int i)
{
	if (i == -1)
	{
		if (shell->cmd->redirect == NULL)
			return (0);
	}
	if (i != -1)
		redir(shell, i);
	while (shell->cmd->redirect)
	{
		if (shell->cmd->redirect->type == REDIRR
			|| shell->cmd->redirect->type == REDIRDR)
			redir_right(shell);
		else if (shell->cmd->redirect->type == REDIRL)
		{
			if (redir_simple_left(shell, i) != 0)
				return (1);
		}
		else if (shell->cmd->redirect->type == REDIRDL)
			redir_heredoc(shell);
		shell->cmd->redirect = shell->cmd->redirect->next;
	}
	return (0);
}
