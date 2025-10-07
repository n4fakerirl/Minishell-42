/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:29:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 15:05:43 by lenakach         ###   ########.fr       */
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
	if (is_builtin(shell->cmd->args[0]))
	{
		shell->exit_status = exec_builtin(shell, &(shell->env));
		exit_status = shell->exit_status;
		free_shell(shell);
		exit(exit_status);
	}
	else
	{
		if (i == 0)
		{
			fprintf(stderr, "je rentre dans first child pour cat -e\n");
			first_child(shell, shell->envp_initial);
		}
		else if (i == shell->nbr_cmd - 1)
		{
			fprintf(stderr, "je rentre dans last child pour wc -l\n");
			last_child(shell, shell->envp_initial);
		}
		else
			inter_child(shell, shell->envp_initial);
	}
}

void	forking_parent(t_shell *shell, int i)
{
	dup2(shell->saved_stdout, STDOUT_FILENO);
	dup2(shell->saved_stdin, STDIN_FILENO);
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	if (shell->cmd->redirect)
	{
		if (shell->cmd->redirect->type == REDIRDL)
			unlink("a");
	}
	if (i == 0)
	{
		fprintf(stderr, "JE CLOSE DANS MON PARENT\n");
		close(shell->pipe_infos->pipe_fd[0][1]);
	}
	else if (i == shell->nbr_cmd - 1)
	{		
		fprintf(stderr, "JE CLOSE DANS MON PARENT POUR MON LAST\n");
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		close(shell->pipe_infos->pipe_fd[i - 1][1]);
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

	i = 0;
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
	//check_heredoc(shell);
	if (shell->nbr_cmd == 1)
		return (one_cmd(shell, shell->envp_initial));
	while (shell->cmd)
	{
		if (i != shell->nbr_cmd - 1)
		{
			if (piping(shell, i) < 0)
				return ;
			printf("PIPING POUR CAT -e\n");
		}
		forking(shell, i);
		if (shell->pipe_infos->pid[i] == 0)
			forking_child(shell, i);
		else if (shell->pipe_infos->pid[i] > 0)
			forking_parent(shell, i);
		i++;
		shell->cmd = shell->cmd->next;
	}
	waiting(shell);
	return ;
}
