/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:20:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/27 15:47:23 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:20:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/27 15:38:58 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_heredoc(t_shell *shell)
{
	char	*line;
	t_cmd	*tmp;
	int		fd[2];
	int		pid;
	int	status;
	t_redir	*tmp_r;
	
	tmp = shell->cmd;
	tmp_r = shell->cmd->redirect;
	while (tmp)
	{
		while (tmp_r)
		{
			if (tmp_r->type == REDIRDL)
			{
				fprintf(stderr, "PREMIER HDC\n");
				if (pipe(fd) == -1)
				{
					perror("pipe");
					return ;
				}
				pid = fork();
				if (pid == 0)
				{
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
					exit (0);
				}
				tmp->here_doc = fd[0];
				close(fd[1]);
				waitpid(pid, &status, 2);
			}
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}


/* void	check_heredoc(t_shell *shell)
{
	char	*line;
	t_cmd	*tmp;
	int		fd[2];

	tmp = shell->cmd;
	while (tmp)
	{
		while (tmp->redirect)
		{
			if (tmp->redirect->type == REDIRDL)
			{
				fprintf(stderr, "PREMIER\n");
				if (pipe(fd) == -1)
				{
					perror("pipe");
					return ;
				}
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, tmp->redirect->file) == 0)
					{
						free(line);
						break ;
					}
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
				close(fd[1]);
				tmp->here_doc = fd[0];
			}
			tmp->redirect = tmp->redirect->next;
		}
		tmp = tmp->next;
	}
} */
