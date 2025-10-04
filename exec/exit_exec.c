/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:19:58 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/22 12:21:02 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void fail_fork(t_shell *shell, int i)
{
	perror("First fork failed\n");
	close(shell->pipe_infos->pipe_fd[i][1]);
	close(shell->pipe_infos->pipe_fd[i - 1][0]);
	shell->exit_status = 1;
}