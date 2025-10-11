/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:35:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 20:23:24 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int	count_list(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	waiting(t_shell *shell)
{
	int	status;
	int	i;

	i = -1;
	while (++i < shell->nbr_cmd)
	{
		waitpid(shell->pipe_infos->pid[i], &status, 0);
		check_signal_exec(shell, &status);
		g_signal = 0;
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	fail_fork(t_shell *shell, int i)
{
	perror("First fork failed\n");
	close(shell->pipe_infos->pipe_fd[i][1]);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	shell->exit_status = 1;
}
