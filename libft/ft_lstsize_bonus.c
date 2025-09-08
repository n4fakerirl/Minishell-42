/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:23:43 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:08 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/*int	main(void)
{
	t_list	*test;
	t_list	*elem1 = malloc(sizeof(t_list));
	elem1->content = ft_strdup("Element1");
	elem1->next = NULL;
	
	t_list	*elem2 = malloc(sizeof(t_list));
	elem2->content = ft_strdup("Element2");
	elem2->next = NULL;

	ft_lstadd_front(&test, elem2);
	ft_lstadd_front(&test, elem1);
	
	printf("%d", ft_lstsize(test));
	return (0);
}*/