/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:29:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 18:43:17 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	piping(t_shell *shell, int i)
{
	if (pipe(shell->pipe_infos->pipe_fd[i]) < 0)
	{
		perror("Error with first pipe");
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	forking(t_shell *shell, int i)
{
	shell->pipe_infos->pid[i] = fork();
	if (shell->pipe_infos->pid[i] < 0)
		return (fail_fork(shell, i));
}

void	forking_child(t_shell *shell, int i)
{
	int	exit_status;

	check_redir(shell, i);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(shell->cmd->args[0]))
	{
		shell->exit_status = exec_builtin(shell, &(shell->env));
		exit_status = shell->exit_status;
		free_shell(shell);
		fprintf(stderr, "JE VAIS EXIT MON BUILTIN\n");
		exit(exit_status);
	}
	else
	{
		if (i == 0)
			first_child(shell, shell->envp_initial);
		else if (i == shell->nbr_cmd - 1)
		{
			fprintf(stderr, "DEUXIEME ENFANT\n");
			last_child(shell, shell->envp_initial);
		}
		else
			inter_child(shell, shell->envp_initial);
	}
}

void	forking_parent(t_shell *shell, int i)
{
	// dup2(shell->saved_stdout, STDOUT_FILENO);
	// dup2(shell->saved_stdin, STDIN_FILENO);
	if (shell->cmd->redirect)
	{
		if (shell->cmd->redirect->type == REDIRDL)
			unlink(shell->cmd->redirect->file);
	}
	if (i == 0)
		close(shell->pipe_infos->pipe_fd[0][1]);
	else if (i == shell->nbr_cmd - 1)
	{		
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		// close(shell->pipe_infos->pipe_fd[i - 1][1]);
	}
	else
	{
		close(shell->pipe_infos->pipe_fd[i][1]);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
	}
}

void	start_exec(t_shell *shell)
{
	int	i;
	int	pid;
	int	ppid;

	i = 0;
	
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
	fprintf(stderr, "MON STDIN : %d\n", shell->saved_stdin);
	fprintf(stderr, "MON STDOUT : %d\n", shell->saved_stdout);
	if (check_heredoc(shell))
		return ;
	if (shell->nbr_cmd == 1)
		return (one_cmd(shell, shell->envp_initial));
	while (shell->cmd)
	{
		if (i != shell->nbr_cmd - 1)
			if (piping(shell, i) < 0)
				return ;
		forking(shell, i);
		// pid = getpid();
		// ppid = getppid();
		// fprintf(stderr, "PID : %d\n", pid);
		// fprintf(stderr, "PPID : %d\n", ppid);
		if (shell->pipe_infos->pid[i] == 0)
			forking_child(shell, i);
		else if (shell->pipe_infos->pid[i] > 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			fprintf(stderr, "PARENT STDIN : %d in %d\n", shell->saved_stdin, pid);
			fprintf(stderr, "PARENT STDOUT : %d in %d\n", shell->saved_stdout, pid);			
			forking_parent(shell, i);
		}
		i++;
		shell->cmd = shell->cmd->next;
	}
	waiting(shell);
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	return ;
}
