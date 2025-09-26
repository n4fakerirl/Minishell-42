/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 17:29:26 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_cmd(t_shell *shell, char **envp_initial)
{
	int	saved_stdout;
	int	saved_stdin;
	
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	check_redir(shell, -1);
	if (is_builtin(shell->cmd->args[0]))
		shell->exit_status = exec_builtin(shell, &(shell->env));
	else
		one_child(shell, envp_initial);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	shell->pipe_infos->pid[0] = fork();
	if (shell->pipe_infos->pid[0] < 0)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (shell->pipe_infos->pid[0] == 0)
	{
		cmd_finale = get_cmd(shell);
		if (!cmd_finale)
		{
			printf("bash: %s: command not found\n", shell->cmd->args[0]);
			shell->exit_status = 127;
			return ;
		}
		if (execve(cmd_finale, shell->cmd->args, envp_initial))
		{
			perror("execve");
			free(cmd_finale);
			exit (127);
		}
	}
}
