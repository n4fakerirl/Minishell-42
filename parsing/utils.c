/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:41:54 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/07 18:52:42 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	backspecial(char c)
{
	if (c == '\\' || c == '"' || c == '$' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}


int	skippable(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

void	ft_lstadd_back_new(t_token **toklist, t_token *token)
{
	t_token	*tmp;

	tmp = *toklist;
	if (!token)
		return ;
	if (!*toklist)
	{
		*toklist = token;
		token->prev = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	token->prev = tmp;
}

int	lstlen(t_token **toklist)
{
	t_token	*tmp;
	int		i;

	tmp = *toklist;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
