/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:24:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 19:05:40 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_done = 1;
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	check_signal_exec(t_shell *shell, int *status)
{
	int	sig;

	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		shell->exit_status = 128 + sig;
	}
	else if (WIFEXITED(*status))
		shell->exit_status = WEXITSTATUS(*status);
	if (WIFEXITED(*status))
		shell->exit_status = WEXITSTATUS(*status);
}

void	check_signal_heredoc(t_shell *shell, int *status, t_cmd *tmp)
{
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		if (tmp->here_doc)
			close(tmp->here_doc);
		shell->heredoc_interrupted = 1;
		shell->exit_status = 130;
	}
}
