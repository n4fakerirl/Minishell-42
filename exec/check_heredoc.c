/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:20:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 17:02:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int exit_test(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (SIGINT);
}

int	fork_heredoc(t_redir *tmp_r, int fd[2], t_shell *shell, t_cmd *tmp)
{
	char	*line;

	(void)shell;
	fprintf(stderr, "MON FD 0 : %d\n", fd[0]);
	fprintf(stderr, "MON FD 1 : %d\n", fd[1]);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			if (tmp->here_doc)
				close(tmp->here_doc);
			if (line)
				free(line);
			free_shell(shell);
			close(fd[1]);
			close(fd[0]);
			return (130);
		}
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
		dprintf(2, "here\n");
	}
	close(fd[1]);
	close(fd[0]);
	free_shell(shell);
	return (0);
}

void	do_heredoc(t_shell *shell, t_cmd *tmp, t_redir *tmp_r, int fd[2])
{
	int	pid;
	int	status;
	int	pid_print;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	fprintf(stderr, "FD 0 APRES PIPE : %d\n", fd[0]);
	fprintf(stderr, "FD 1 APRES PIPE: %d\n", fd[1]);
	pid = fork();
	pid_print = getpid();
	if (pid == 0)
	{
		fprintf(stderr, "MON PIED DANS HEREDOC CHILD:%d\n", pid_print);
		rl_event_hook = exit_test;
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_DFL);
		status = fork_heredoc(tmp_r, fd, shell, tmp);
		exit (status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		tmp->here_doc = fd[0];
		fprintf(stderr, "FD 0 DANS PARENT : %d\n", fd[0]);
		fprintf(stderr, "STDIN DANS PARENT : %d\n", shell->saved_stdin);
		fprintf(stderr, "STDOUT DANS PARENT : %d\n", shell->saved_stdout);		close(fd[1]);
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
				{
					fprintf(stderr, "JE CLSOE 0 AU PREMIER HEREDCO\n");
					close(fd[0]);
				}
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
