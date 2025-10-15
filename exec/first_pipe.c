/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:46:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 21:36:38 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		failed_cmd_execve(shell);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		ft_putstr_fd("bash:", 2);
		ft_putstr_fd(shell->cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		free_exit(shell);
		exit(127);
	}
	execve(cmd_finale, shell->cmd->args, envp_initial);
	failed_cmd_execve(shell);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	perror("execve");
	free(cmd_finale);
	free_exit(shell);
	exit(127);
}
