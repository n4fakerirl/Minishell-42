/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 15:20:46 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	forking_one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		dup2(shell->saved_stdin, STDIN_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		printf("bash: %s: command not found\n", shell->cmd->args[0]);
		shell->exit_status = 127;
		exit(127);
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

void	one_child(t_shell *shell, char **envp_initial)
{
	int	status;
	int	sig;

	shell->pipe_infos->pid[0] = fork();
	if (shell->pipe_infos->pid[0] < 0)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (shell->pipe_infos->pid[0] == 0)
		forking_one_child(shell, envp_initial);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(shell->pipe_infos->pid[0], &status, 0);
		if (WIFSIGNALED(status))
		{
			 sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			shell->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		g_signal = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	one_cmd(t_shell *shell, char **envp_initial)
{
	check_redir(shell, -1);
	if (is_builtin(shell->cmd->args[0]))
		shell->exit_status = exec_builtin(shell, &(shell->env));
	else
		one_child(shell, envp_initial);
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
}
