/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:04:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:57:52 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*int	main(void)
{
	unsigned char	str[9] = "Hello124&";

	printf("Ma chaine avant bzero : %s\n", str);
	ft_bzero(str, 5);
	printf("Ma chaine apres bzero %s", str);
	return (0);
}*/