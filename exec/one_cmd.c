/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 14:05:50 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;
	int	status;

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
			dup2(shell->saved_stdout, STDOUT_FILENO);
			dup2(shell->saved_stdin, STDIN_FILENO);
			close(shell->saved_stdin);
			close(shell->saved_stdout);
			printf("bash: %s: command not found\n", shell->cmd->args[0]);
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
			exit (127);
		}
	}
	else
	{
		waitpid(shell->pipe_infos->pid[0], &status, 2);
	}
}

void	one_cmd(t_shell *shell, char **envp_initial)
{
	check_redir(shell, -1);
	if (is_builtin(shell->cmd->args[0]))
		shell->exit_status = exec_builtin(shell, &(shell->env));
	else
		one_child(shell, envp_initial);
	fprintf(stderr, "JE SUI SORTIE\n");
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
}

