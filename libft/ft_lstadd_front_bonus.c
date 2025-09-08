/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:20:06 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:21 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
/*int	main(void)
{
	t_list	*head = NULL;
	t_list	*elem1 = malloc(sizeof(t_list));
	elem1->content = ft_strdup("Hello");
	elem1->next = NULL;

	t_list	*elem2 = malloc(sizeof(t_list));
	elem2->content = ft_strdup("World");
	elem2->next = NULL;

	ft_lstadd_front(&head, elem1);
	ft_lstadd_front(&head, elem2);

	t_list	*current = head;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}*/