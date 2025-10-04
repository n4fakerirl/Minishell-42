/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:16:34 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/27 11:21:51 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inter_child(t_shell *shell, char **envp_initial)
{	
	char	*cmd_finale;
	
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		dup2(shell->saved_stdin, STDIN_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		printf("PROBLEM WITH FIRST PIPE GET CMD\n");
		shell->exit_status = 127;
		return ;
	}
	if (execve(cmd_finale, shell->cmd->args, envp_initial))
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		dup2(shell->saved_stdin, STDIN_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		perror("execve");
		free(cmd_finale);
		exit(127);
	}
}
