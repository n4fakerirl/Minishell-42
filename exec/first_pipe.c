/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:46:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/16 18:47:44 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child(t_shell *shell, char **envp_initial)
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
	free(cmd_finale);
	free_exit(shell);
	exit(127);
}
