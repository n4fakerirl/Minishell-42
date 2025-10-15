/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:46:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 19:41:15 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		dup2(shell->saved_stdin, STDIN_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		ft_putstr_fd("bash:", 2);
		ft_putstr_fd(shell->cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		free_exit(shell);
		exit (127);
	}
	execve(cmd_finale, shell->cmd->args, envp_initial);
	if (duping(shell) == 1)
		return ;
	perror("execve");
	free(cmd_finale);
	free_exit(shell);
	exit(127);
}
