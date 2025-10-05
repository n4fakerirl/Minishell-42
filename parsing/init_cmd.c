/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:03:39 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/05 20:59:59 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir(t_redir **redirs, t_redir *node)
{
	t_redir	*tmp;

	tmp = *redirs;
	if (!*redirs)
	{
		*redirs = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

t_redir	*redirections(t_cmd *cmd, t_token *token)
{
	t_redir	*node;
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type >= 2 && tmp->type <= 5)
		{
			if (tmp->next && tmp->next->type == ARGREDIR)
			{
				node = malloc(sizeof(t_redir));
				node->type = tmp->type;
				node->file = ft_strdup(tmp->next->value);
				add_redir(&(cmd->redirect), node);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (cmd->redirect);
}

void	add_cmds(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
	cmd->next = NULL;
}

void	cmd_list(t_token *tokens, t_cmd **cmds, t_env *env, int exit_status)
{
	t_token	*tmp;
	t_cmd	*current;
	t_token	*start;
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
		start = tmp;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD)
			{
				if (tmp->need_exp == true)
				{
					str = expand(tmp, env, exit_status);
					if (str != NULL)
						current->args[i] = ft_strdup(str);
					printf("args[%d] : %s\n", i, current->args[i]);
					i++;
				}
				else
				{
					if (tmp->value[0] != '\0' && tmp->value != NULL)
					{
						current->args[i] = del_back(tmp);
						printf("args[%d] : %s\n", i, current->args[i]);
						i++;
					}
				}
			}
			tmp = tmp->next;
		}
		current->args[i] = NULL;
		current->redirect = redirections(current, start);
		if (tmp && tmp->type == PIPE)
		{
			current->is_pipe = true;
			tmp = tmp->next;
		}
	}
}
