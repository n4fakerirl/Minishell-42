/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:28 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 17:49:02 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(t_cmd **cmds)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd)); // Initialise la structure à zéro
	if (!*cmds)
	{
		*cmds = cmd;
	}
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	cmd->next = NULL;
	return (cmd);
}

void	create_cmd(t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
    while (tm)
	while (tmp != NULL && tmp->type != PIPE)
	{
        
		tmp = tmp->next;
	}
}
