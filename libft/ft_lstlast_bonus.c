/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:02:27 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*int	main(void)
{
	t_list	*test = NULL;
	t_list	*elem1 = malloc(sizeof(t_list));
	elem1->content = ft_strdup("Element1");
	elem1->next = NULL;

	t_list	*elem2 = malloc(sizeof(t_list));
	elem2->content = ft_strdup("Element2");
	elem2->next = NULL;

	ft_lstadd_front(&test, elem2);
	ft_lstadd_front(&test, elem1);

	printf("%s", (char *)ft_lstlast(test)->content);
	return (0);
}*/