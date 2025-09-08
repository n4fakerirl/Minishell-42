/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:05:36 by ocviller          #+#    #+#             */
/*   Updated: 2025/05/05 20:37:01 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmpnext;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmpnext = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = tmpnext;
	}
	del(tmp->content);
	free(tmp);
	*lst = NULL;
}
