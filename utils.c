/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:17:24 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 13:36:21 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_token **toklist, t_token *token)
{
	t_token	*tmp;

	tmp = *toklist;
	if (!*toklist)
	{
		*toklist = token;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}
