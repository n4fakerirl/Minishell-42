/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:28 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/12 16:39:03 by ocviller         ###   ########.fr       */
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

int parse_args(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            if (!tmp->prev || !tmp->next || tmp->prev->type != WORD || tmp->next->type != WORD)
                return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
        }
        else if (tmp->type == REDIRR || tmp->type == REDIRL)
        {
            if ((!tmp->prev && !tmp->next))
               return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
            else if (tmp->prev && tmp->type == REDIRL && tmp->prev->type >= 2 && tmp->prev->type <= 5)
                return (printf("minishell: syntax error near unexpected token `<'\n"), 0);
            else if (tmp->prev && tmp->prev->type == REDIRL && tmp->type == REDIRR && !tmp->next)
                return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
            else if (tmp->prev && tmp->type == REDIRR && tmp->prev->type >= 2 && tmp->prev->type <= 5)
                return (printf("minishell: syntax error near unexpected token `>'\n"), 0);
            else if (!tmp->next)
                return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
        }
        else if (tmp->type == REDIRDR || tmp->type == REDIRDL)
        {
            if ((!tmp->prev && !tmp->next) || !tmp->next)
                return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
            else if (tmp->prev && tmp->type == REDIRDR && tmp->prev->type >= 2 && tmp->prev->type <= 5)
                return (printf("minishell: syntax error near unexpected token `>>'\n"), 0);
            else if (tmp->prev && tmp->type == REDIRDL && tmp->prev->type >= 2 && tmp->prev->type <= 5)
                return (printf("minishell: syntax error near unexpected token `<<'\n"), 0);
        }
        tmp = tmp->next;
    }
    return (1);
}
