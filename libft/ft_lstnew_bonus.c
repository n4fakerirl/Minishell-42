/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:06:45 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:59 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
 */

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = malloc (sizeof(t_list));
	if (!ptr)
		return (NULL);
	(*ptr).content = content;
	(*ptr).next = NULL;
	return (ptr);
}

/* int	main(void)
{
	t_list	*tmp;

	tmp = ft_lstnew((void *)5);

	printf("%d", (int *)(*tmp).content);
	return (0);
}
 */
/* int	main(void)
{
	t_list	*tmp;

	tmp = ft_lstnew((void *)"Heyyy");

	printf("%s", (char *)(*tmp).content);
	return (0);
} */
