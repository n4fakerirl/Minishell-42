/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:29:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/23 13:51:48 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir(t_shell *shell, int i)
{
	if (i == 0)
	{
		fprintf(stdin, "Mon i == 0 dans redir\n");
		dup2(shell->pipe_infos->pipe_fd[0][1], 1);
		close(shell->pipe_infos->pipe_fd[0][1]);
		close(shell->pipe_infos->pipe_fd[0][0]);
		return ;
	}
	if (i == shell->nbr_cmd - 1)
	{
		fprintf(stderr, "REDIR DE MA [%d]eme commande\n", i);
		dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		close(shell->pipe_infos->pipe_fd[i - 1][1]);
		return ;
	}
	else
	{
		dup2(shell->pipe_infos->pipe_fd[i][1], 1);
		dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
		close(shell->pipe_infos->pipe_fd[i][0]);
		close(shell->pipe_infos->pipe_fd[i][1]);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		return ;
	}
}

int	piping(t_shell *shell, int i)
{
	if (pipe(shell->pipe_infos->pipe_fd[i]) < 0)
	{
		perror("Error with first pipe");
		shell->exit_status = 1;
		return (1);
	}
	printf("Etape 2 : piping au rang [%d]\n", i);
	return (0);
}

void	start_exec(t_shell *shell, int i)
{
	int	exit_status;

	if (shell->nbr_cmd == 1)
		return (one_cmd(shell, shell->envp_initial));
	if (i != shell->nbr_cmd - 1)
		if (piping(shell, i))
			return ;
	fprintf(stderr, "Etape 3 : Je fork au rang [%d]\n", i);
	shell->pipe_infos->pid[i] = fork();
	printf("MON PID EST : %d au rang %d\n", getpid(), i);
	if (shell->pipe_infos->pid[i] < 0)
		return (fail_fork(shell, i));
	else if (shell->pipe_infos->pid[i] == 0)
	{
		if (is_builtin(shell->cmd->args[0]))
		{
			fprintf(stderr, "Etape 4 : Je suis un builtin au rang [%d]\n", i);
			redir(shell, i);
			fprintf(stderr, "Etape 5 : je fais mes redirections au rang [%d]\n", i);
			shell->exit_status = exec_builtin(shell, &(shell->env));
			exit_status = shell->exit_status;
			free_shell(shell);
			fprintf(stderr, "Etape 6 : exec_builtin au rang [%d]\n", i);
			exit(exit_status);
		}
		else
		{
			fprintf(stderr, "Etape 4 : Je suis une commande au rang [%d]\n", i);
			if (i == 0)
				first_child(shell, shell->envp_initial);
			else if (i == shell->nbr_cmd - 1)
				last_child(shell, shell->envp_initial, i);
			else
				inter_child(shell, shell->envp_initial, i);
		}
	}
	else if (shell->pipe_infos->pid[i] > 0)
	{
		if (i == 0)
		{
			fprintf(stdout, "i == 0 : Le parent ferme les bons fd\n");
			close(shell->pipe_infos->pipe_fd[0][1]);
		}
		else if (i == shell->nbr_cmd - 1)
		{
			close(shell->pipe_infos->pipe_fd[i - 1][0]);
			close(shell->pipe_infos->pipe_fd[i - 1][1]);
		}
		else
		{
			close(shell->pipe_infos->pipe_fd[i][1]);
			close(shell->pipe_infos->pipe_fd[i - 1][0]);
		}
	}
	fprintf(stdout, "Je sors de mon exec\n");
	return ;
}
