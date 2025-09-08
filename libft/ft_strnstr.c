/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:49 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 14:00:05 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && (i + j) < len)
		{		
			j++;
			if (little [j] == 0)
				return ((char *)(&big[i]));
		}
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const char	big[] = "lorem ipsum dolor sit amet";
	const char	little[] = "lorem";

	printf("Mon retour : %s", ft_strnstr(big, little, 15));
	return (0);
}*/