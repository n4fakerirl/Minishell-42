/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:21:29 by ocviller          #+#    #+#             */
/*   Updated: 2025/05/05 16:44:41 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		y = 0;
		while (big[y + i] && little[y] && big[y + i] == little[y]
			&& (i + y) < len)
			y++;
		if (little[y] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
