/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 19:56:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/03 20:01:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	if (!token)
		return ;
	while (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		next = tmp->next;
		free(tmp->prev);
		free(tmp);
		tmp = next;
	}
}
