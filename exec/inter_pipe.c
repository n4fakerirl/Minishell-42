/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:16:34 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 12:15:23 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inter_child(t_shell *shell, char **envp_initial, int i)
{	
	char	*cmd_finale;
	(void)i;
	
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		printf("PROBLEM WITH FIRST PIPE GET CMD\n");
		shell->exit_status = 127;
		return ;
	}
	/* dup2(shell->pipe_infos->pipe_fd[i][1], 1);
	dup2(shell->pipe_infos->pipe_fd[i - 1][0], 0);
	close(shell->pipe_infos->pipe_fd[i][1]);
	close(shell->pipe_infos->pipe_fd[i][0]);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	close(shell->pipe_infos->pipe_fd[i - 1][1]); */
	if (execve(cmd_finale, shell->cmd->args, envp_initial))
	{
		perror("execve");
		free(cmd_finale);
		exit(127);
	}
}

/* void	inter_pipe(t_shell *shell, char **envp_initial, int i, char *cmd_finale)
{
	//int nbr_cmd;
	//int index_pipe;

	shell->pipe_infos->pid[i] = fork();
	if (shell->pipe_infos->pid[i] < 0)
	{
		perror("First fork failed\n");
		close(shell->pipe_infos->pipe_fd[i][1]);
		close(shell->pipe_infos->pipe_fd[i - 1][0]);
		shell->exit_status = 1;
		return ;
	}
	if (shell->pipe_infos->pid[i] == 0)
		inter_child(shell, envp_initial, i, cmd_finale);
	return ;
} */
