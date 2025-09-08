/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:43:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:10 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;
	unsigned char		uc;

	str = (const unsigned char *)s;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(&str[i]));
		else
			i++;
	}
	return (NULL);
}
/*int	main(void)
{
	char	str[] = 0;
	int		c = 0;
	unsigned char	*ptr;

	ptr = ft_memchr(str, c, 5);
	printf("L'adresse est : %p", ptr);
	return (0);
}*/