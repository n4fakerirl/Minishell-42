/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:32:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/16 18:44:09 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_last(t_shell *shell)
{
	free_exit(shell);
	exit(127);
}

void	cmd_not(t_shell *shell)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(shell->cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	last_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		shell->exit_status = 127;
		if (!shell->cmd->args[0])
			free_last(shell);
		cmd_not(shell);
		free_last(shell);
	}
	execve(cmd_finale, shell->cmd->args, envp_initial);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	perror("execve");
	free_exit(shell);
	free(cmd_finale);
	exit(127);
}
