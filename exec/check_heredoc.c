/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:20:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 14:59:14 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_heredoc(t_redir *tmp_r, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			fprintf(stderr, "minishell: warning: ");
			fprintf(stderr,
				"here-document delimited by end-of-file (wanted '%s')\n",
				tmp_r->file);
			break ;
		}
		if (ft_strcmp(line, tmp_r->file) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

void	do_heredoc(t_shell *shell, t_cmd *tmp, t_redir *tmp_r, int fd[2])
{
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fork_heredoc(tmp_r, fd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		tmp->here_doc = fd[0];
		close(fd[1]);
		waitpid(pid, &status, 0);
		check_signal_heredoc(shell, &status);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	check_heredoc(t_shell *shell)
{
	t_cmd	*tmp;
	t_redir	*tmp_r;
	int		fd[2];

	if (!shell->cmd->redirect)
		return (0);
	tmp = shell->cmd;
	tmp_r = shell->cmd->redirect;
	while (tmp)
	{
		while (tmp_r)
		{
			if (tmp_r->type == REDIRDL)
			{
				do_heredoc(shell, tmp, tmp_r, fd);
				if (shell->heredoc_interrupted == 1)
				{
					shell->heredoc_interrupted = 0;
					return (1);
				}
			}
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
