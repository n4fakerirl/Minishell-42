/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:24:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 18:42:58 by lenakach         ###   ########.fr       */
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

void	redir_simple_left(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirect->file, O_RDONLY);
	if (fd < 0)
		return (perror(""));
	dup2(fd, 0);
	close(fd);
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

void	check_redir(t_shell *shell, int i)
{
	t_redir	*r;

	if (!shell || !shell->cmd)
		return ;
	if (i == -1)
	{
		if (shell->cmd->redirect == NULL)
			return ;
	}
	if (i != -1)
		redir(shell, i);
	r = shell->cmd->redirect;
	while (r)
	{
		if (r->type == REDIRR || r->type == REDIRDR)
			redir_right(shell);
		else if (r->type == REDIRL)
			redir_simple_left(shell);
		else if (r->type == REDIRDL)
			redir_heredoc(shell);
		r = r->next;
	}
	return ;
}

// void	check_redir(t_shell *shell, int i)
// {
//     t_redir *redirl;

//     if (i == -1)
//     {
//         if (shell->cmd->redirect == NULL)
//             return ;
//     }
//     if (i != -1)
//         redir(shell, i);
//     redirl = shell->cmd->redirect; // Utilise un pointeur temporaire
//     while (redirl)
//     {
//         if (redirl->type == REDIRR || redirl->type == REDIRDR)
//             redir_right(shell);
//         else if (redirl->type == REDIRL)
//             redir_simple_left(shell);
//         else if (redirl->type == REDIRDL)
//             redir_heredoc(shell);
//         redirl = redirl->next;
//     }
//     return ;
// }
