/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 19:41:49 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	forking_one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	cmd_finale = get_cmd(shell);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
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
		exit(127);
	}
	execve(cmd_finale, shell->cmd->args, envp_initial);
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	perror("execve");
	free(cmd_finale);
	free_exit(shell);
	exit(127);
}

void	one_child(t_shell *shell, char **envp_initial)
{
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		forking_one_child(shell, envp_initial);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(shell->pipe_infos->pid[0], &status, 0);
		check_signal_exec(shell, &status);
		g_signal = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	one_cmd(t_shell *shell, char **envp_initial)
{
	int	pid;

	pid = getpid();
	if (check_redir(shell, -1) != 0)
		return ;
	if (is_builtin(shell->cmd->args[0]))
		shell->exit_status = exec_builtin(shell, &(shell->env));
	else
		one_child(shell, envp_initial);
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
}
