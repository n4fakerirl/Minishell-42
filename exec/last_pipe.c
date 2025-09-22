/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:32:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/21 16:41:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	last_child(t_shell *shell, char **envp_initial, int i)
{
	int	nbr_cmd;
	char *cmd_finale;
	
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		printf("PROBLEM WITH FIRST PIPE GET CMD\n");
		shell->exit_status = 127;
		return ;
	}
	nbr_cmd = count_list(shell->cmd);
	dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	close(shell->pipe_infos->pipe_fd[i - 1][1]);
	if (execve(cmd_finale, shell->cmd->args, envp_initial))
	{
		perror("execve");
		free(cmd_finale);
		exit (127);
	}
}
/* 
void	last_pipe(t_shell *shell, char **envp_initial, char *cmd_finale)
{	
	int	nbr_cmd;
	int	index_pipe;

	nbr_cmd = count_list(shell->cmd);
	index_pipe = nbr_cmd - 2;
	shell->pipe_infos->pid[nbr_cmd - 1] = fork();
	if (shell->pipe_infos->pid[nbr_cmd - 1] < 0)
	{
		close(shell->pipe_infos->pipe_fd[index_pipe][0]);
		perror("Last fork failed");
		shell->exit_status = 1;
		return ;
	}
	if (shell->pipe_infos->pid[nbr_cmd - 1] == 0)
		last_child(shell, envp_initial, cmd_finale);
	return ;
} */
