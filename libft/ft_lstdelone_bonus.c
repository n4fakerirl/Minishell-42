/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:44:06 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:26 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*void	del_test(void *content)
{
	free(content);
	printf("Concent deleted\n");
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/*int	main(void)
{
	t_list	*test = NULL;
	t_list	*elem1 = malloc(sizeof(t_list));
	elem1->content = ft_strdup("Hello");
	elem1->next = NULL;
	t_list	*elem2 = malloc(sizeof(t_list));
	elem2->content = ft_strdup("Salut");
	elem2->next = NULL;
	t_list	*elem3 = malloc(sizeof(t_list));
	elem3->content = ft_strdup("Chalom");
	elem3->next = NULL;
	ft_lstadd_front(&test, elem1);
	ft_lstadd_front(&test, elem2);
	ft_lstadd_front(&test, elem3);
	t_list	*current = test;
	while (current)
	{
		printf("%s\n", (char *)(current->content));
		current = current->next;
	}
	ft_lstdelone(elem1, del_test);
	return (0);
}*/
