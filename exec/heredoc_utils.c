/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:14:17 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/14 13:46:43 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	exit_ctrlc(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (SIGINT);
}

void	free_exit(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp_initial)
		free_split(shell->envp_initial);
	if (shell->head_cmd)
		free_cmd(shell->head_cmd);
	if (shell->env)
		free_env(shell->env);
	if (shell->pipe_infos)
		free(shell->pipe_infos);
	if (shell->saved_stdin)
		close(shell->saved_stdin);
	if (shell->saved_stdout)
		close(shell->saved_stdout);
	if (shell->data)
	{
		if (shell->data->tmp)
			free_env(shell->data->tmp);
		free(shell->data);
	}
	free(shell);
}
