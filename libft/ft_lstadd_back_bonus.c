/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:35:18 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/03 18:31:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
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

	t_list	*new = malloc(sizeof(t_list));
	new->content = ft_strdup("Quetal");
	new->next = NULL;

	ft_lstadd_front(&head, elem1);
	ft_lstadd_front(&head, elem2);

	ft_lstadd_back(&head, new);

	t_list	*current = head;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}*/