/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:06:50 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (i < n)
	{	
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*int	main(void)
{
	char	test[] = "Hello";
	char	test2[] = "";
	unsigned char	*res;

	res = ft_memcpy(test2, test, 10);
	printf("Ma dest apres : %s\n", res);
	return (0);
}*/