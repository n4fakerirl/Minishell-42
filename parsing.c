/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:28 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/29 11:27:28 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_list(t_token *tokens, t_cmd **cmds, t_env *env)
{
	t_token	*tmp;
	t_cmd	*current;
	char	*str;
	int		i;

	tmp = tokens;
	current = NULL;
	while (tmp)
	{
		current = malloc(sizeof(t_cmd));
		if (!current)
			return ;
		ft_bzero(current, sizeof(t_cmd));
		add_cmds(cmds, current);
		current->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
		if (!current->args)
			return ;
		i = 0;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->need_exp == true)
			{
				str = expand(tmp, env);
				if (str != NULL)
					current->args[i++] = ft_strdup(str);
			}
			else
				current->args[i++] = del_back(tmp);
			tmp = tmp->next;
		}
		current->args[i] = NULL;
		if (tmp && tmp->type == PIPE)
		{
			current->is_pipe = true;
			tmp = tmp->next;
		}
	}
}

int	simple_redir(t_token *tmp)
{
	if ((!tmp->prev && !tmp->next))
		return (printf("minishell: syntax error near unexpected token `newline'\n"),
			0);
	else if (tmp->prev && tmp->type == REDIRL && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printf("minishell: syntax error near unexpected token `<'\n"),
			0);
	else if (tmp->prev && tmp->prev->type == REDIRL && tmp->type == REDIRR
		&& !tmp->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"),
			0);
	else if (tmp->prev && tmp->type == REDIRR && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printf("minishell: syntax error near unexpected token `>'\n"),
			0);
	else if (!tmp->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"),
			0);
	return (1);
}

int	double_redir(t_token *tmp)
{
	if ((!tmp->prev && !tmp->next) || !tmp->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"),
			0);
	else if (tmp->prev && tmp->type == REDIRDR && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printf("minishell: syntax error near unexpected token `>>'\n"),
			0);
	else if (tmp->prev && tmp->type == REDIRDL && tmp->prev->type >= 2
		&& tmp->prev->type <= 5)
		return (printf("minishell: syntax error near unexpected token `<<'\n"),
			0);
	return (1);
}

int	parse_args(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->prev || !tmp->next || tmp->prev->type != WORD)
				return (printf("minishell: syntax error near unexpected token `|'\n"),
					0);
		}
		else if (tmp->type == REDIRR || tmp->type == REDIRL)
		{
			if (simple_redir(tmp) == 0)
				return (0);
		}
		else if (tmp->type == REDIRDR || tmp->type == REDIRDL)
		{
			if (double_redir(tmp) == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
