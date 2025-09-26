/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:46:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 13:14:12 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child(t_shell *shell, char **envp_initial)
{
	char *cmd_finale;
	
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		printf("PROBLEM WITH FIRST PIPE GET CMD\n");
		shell->exit_status = 127;
		return ;
	}
	fprintf(stderr, "JE VIAS EXECVE\n");
/* 	dup2(shell->pipe_infos->pipe_fd[0][1], 1);
	close(shell->pipe_infos->pipe_fd[0][1]);
	close(shell->pipe_infos->pipe_fd[0][0]); */
	if (execve(cmd_finale, shell->cmd->args, envp_initial))
	{
		perror("execve");
		free(cmd_finale);
		exit (127);
	}
}

/* void	first_pipe(t_shell *shell, char **envp_initial, char *cmd_finale)
{
	shell->pipe_infos->pid[0] = fork();
	if (shell->pipe_infos->pid[0] < 0)
	{
		perror("First fork failed\n");
		shell->exit_status = 1;
		return ;
	}
	if (shell->pipe_infos->pid[0] == 0)
		first_child(shell, envp_initial, cmd_finale);
	return ;
} */


