/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:20:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 22:45:56 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_heredoc(t_redir *tmp_r, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, tmp_r->file) == 0)
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

void	do_heredoc(t_cmd *tmp, t_redir *tmp_r, int fd[2])
{
	int	pid;
	int	status;
	
	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == 0)
		fork_heredoc(tmp_r, fd);
	tmp->here_doc = fd[0];
	close(fd[1]);
	waitpid(pid, &status, 2);
}

void	check_heredoc(t_shell *shell)
{
	t_cmd	*tmp;
	t_redir	*tmp_r;
	int		fd[2];

	tmp = shell->cmd;
	tmp_r = shell->cmd->redirect;
	while (tmp)
	{
		while (tmp_r)
		{
			if (tmp_r->type == REDIRDL)
				do_heredoc(tmp, tmp_r, fd);
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
