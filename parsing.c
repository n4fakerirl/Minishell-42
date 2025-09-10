/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:28 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 20:52:36 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_list(t_token *tokens, t_cmd **cmds)
{
    t_token *tmp = tokens;
    t_cmd *current = NULL;
    int i;

    while (tmp)
    {
        current = malloc(sizeof(t_cmd));
        if (!current)
            return;
        ft_bzero(current, sizeof(t_cmd));
        add_cmds(cmds, current);
        current->args = malloc(sizeof(char *) * (lstlen(&tokens) + 1));
        if (!current->args)
            return;
        i = 0;
        while (tmp && tmp->type != PIPE)
        {
            current->args[i++] = ft_strdup(tmp->value);
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
