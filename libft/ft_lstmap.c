/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:49:51 by ocviller          #+#    #+#             */
/*   Updated: 2025/05/14 14:44:34 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		elem = ft_lstnew(new_content);
		if (!elem)
		{
			del(new_content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
