/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:32:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 19:31:07 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	last_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		// dup2(shell->saved_stdout, STDOUT_FILENO);
		// dup2(shell->saved_stdin, STDIN_FILENO);
		// close(shell->saved_stdin);
		// close(shell->saved_stdout);
		shell->exit_status = 127;
		free_shell(shell);
		exit(127);
	}
	dprintf(2, "Salut !\n");
	if (execve(cmd_finale, shell->cmd->args, envp_initial))
	{
		// dup2(shell->saved_stdout, STDOUT_FILENO);
		// dup2(shell->saved_stdin, STDIN_FILENO);
		// close(shell->saved_stdin);
		// close(shell->saved_stdout);
		perror("execve");
		free_shell(shell);
		free(cmd_finale);
		exit(127);
	}
}
