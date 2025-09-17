/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:46:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 19:04:23 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_pipe(t_shell *shell)
{
	if (pipe(shell->pipe_infos->pipe_fd[0]))
	{
		perror("Error with first pipe");
		shell->exit_status = 1;
		return ;
	}
	shell->pipe_infos->pid[0] = fork();
	if (shell->pipe_infos->pid[0] < 0)
	{
		close(shell->pipe_infos->pipe_fd[0][1]);
		perror("First fork failed\n");
		shell->exit_status = 1;
		return ;
	}
	if (shell->pipe_infos->pid == 0)
		first_child(shell);
	else
		close(shell->pipe_infos->pipe_fd[0][1]);
}

void	first_child(t_shell *shell)
{
	dup2(shell->pipe_infos->pipe_fd[0][1], 1);
}

void	one_pipe(t_shell *shell)
{
	first_pipe(shell);
	
}

