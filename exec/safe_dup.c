/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:55:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/16 18:10:05 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	safe_main_dup(t_shell *shell)
{
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
	{
		perror("dup STDIN");
		shell->exit_status = 1;
		return (-1);
	}
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
	{
		perror("dup STDOUT");
		close(shell->saved_stdin);
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	safe_redir_dup(t_shell *shell, int fd, int i)
{
	if (dup2(fd, 0) == -1)
	{
		perror("dup 2 (in redir)");
		close(fd);
		if (i == -1)
			return (1);
		else
		{
			free_exit(shell);
			exit(1);
		}
	}
	return (0);
}

int	safe_dup2(int oldfd, int newfd, const char *context)
{
	if (dup2(oldfd, newfd) == -1)
	{
		if (*context)
			perror(context);
		return (1);
	}
	return (0);
}

void	failed_cmd_execve(t_shell *shell)
{
	if (safe_dup2(shell->saved_stdout, STDOUT_FILENO, "") == 1)
	{
		free_exit(shell);
		exit(1);
	}
	if (safe_dup2(shell->saved_stdin, STDIN_FILENO, "") == 1)
	{
		free_exit(shell);
		exit(1);
	}
	close(shell->saved_stdin);
	close(shell->saved_stdout);
}
