/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:16:50 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:42 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	cc;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)(&s[i]));
		i++;
	}
	if (s[i] == cc)
		return ((char *)(&s[i]));
	return (NULL);
}
/*int	main(void)
{
	const char	str[] = "Hola";
	int			c;

	c = 72;
	printf("Mon retour : %p", ft_strchr(str, c));
	return (0);
}*/