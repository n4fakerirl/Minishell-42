/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:43:40 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/16 16:44:58 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	closing(t_redir *tmp_r, int fd[2], t_shell *shell)
{
	if (tmp_r->next && tmp_r->next->type == REDIRDL)
		close(fd[0]);
	if (shell->heredoc_interrupted == 1)
		return (shell->heredoc_interrupted = 0, 1);
	return (0);
}

int	need_exp_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (ft_strchr(str, '$'))
	{
		while (str[i] != '$')
			i++;
		if (is_expandable(str + i) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	expand_line(char **line, t_shell *shell, t_redir *tmp_r)
{
	char	*expanded;

	expanded = NULL;
	if (need_exp_str(*line))
	{
		expanded = expand_word(*line, shell->env, 0, 0);
		if (!expanded)
			return (0);
		free(*line);
		*line = expanded;
	}
	if (ft_strcmp(*line, tmp_r->file) == 0)
	{
		free(*line);
		return (0);
	}
	return (1);
}

void	close_unused_heredocs(t_shell *shell, t_cmd *current_cmd)
{
	t_cmd	*tmp;

	tmp = shell->head_cmd;
	while (tmp)
	{
		if (tmp != current_cmd && tmp->here_doc > 2)
		{
			close(tmp->here_doc);
			tmp->here_doc = -1;
		}
		tmp = tmp->next;
	}
}
