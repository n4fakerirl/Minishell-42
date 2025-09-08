/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:10:19 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:13 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	i = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (i < n)
	{
		if (!(c1[i] == c2[i]))
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char	*s1 = "abcdefghij";
	char	*s2 = "abcdefgxyz";
	int		res = ft_memcmp(s1, s2, 7);

	printf("%d", res);
	return (0);
}*/