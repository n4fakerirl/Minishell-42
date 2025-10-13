/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:12:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 19:58:02 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ctrlc_action(t_cmd *tmp, char *line, t_shell *shell, int fd[2])
{
	if (tmp->here_doc)
		close(tmp->here_doc);
	if (line)
		free(line);
	free_exit(shell);
	close(fd[1]);
	close(fd[0]);
	return (130);
}

void	printing_ctrld(t_redir *tmp_r)
{
	ft_putendl_fd("minishell: warning: ", 2);
	ft_putendl_fd("here-document delimited by end-of-file (wanted '", 2);
	ft_putendl_fd(tmp_r->file, 2);
	ft_putendl_fd("')", 2);
	ft_putendl_fd("\n", 2);
}

int	fork_heredoc(t_redir *tmp_r, int fd[2], t_shell *shell, t_cmd *tmp)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (ctrlc_action(tmp, line, shell, fd));
		if (!line)
		{
			printing_ctrld(tmp_r);
			break ;
		}
		line = expand_word(line, shell->env, 0, 0);
		if (ft_strcmp(line, tmp_r->file) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	close(fd[0]);
	return (free_exit(shell), 0);
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
		rl_event_hook = exit_ctrlc;
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_DFL);
		status = fork_heredoc(tmp_r, fd, shell, tmp);
		exit(status);
	}
	else
	{
		signal_heredoc();
		tmp->here_doc = fd[0];
		close(fd[1]);
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
		check_signal_heredoc(shell, &status, tmp);
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
				if (tmp_r->next && tmp_r->next->type == REDIRDL)
					close(fd[0]);
				if (shell->heredoc_interrupted == 1)
					return (shell->heredoc_interrupted = 0, 1);
			}
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
