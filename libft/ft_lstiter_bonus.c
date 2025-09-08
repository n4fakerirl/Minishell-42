/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:03:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:30 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*void	f_test(void *ptr)
{
	unsigned char	*str;
	int				i;

	i = 0;
	str = (unsigned char *)(ptr);
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
}*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*int	main(void)
{
	t_list	*head;

	t_list	*elem1 = malloc(sizeof(t_list));
	elem1->content = ft_strdup("Hello");
	elem1->next = NULL;

	t_list	*elem2 = malloc(sizeof(t_list));
	elem2->content = ft_strdup("Salam");
	elem2->next = NULL;

	ft_lstadd_front(&head, elem1);
	ft_lstadd_front(&head, elem2);

	ft_lstiter(head, f_test);

	t_list	*current = head;
	while (current)
	{
		printf("%s\n", (unsigned char *)current->content);
		current = current->next;
	}
	return (0);
}*/