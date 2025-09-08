/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:45:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:47 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*void	ft_test(unsigned int i, char *s)
{
	if (i % 2 == 0 && (*s >= 'A' && *s <= 'Z'))
		*s = *s + 32;
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*int	main(void)
{
	char	str[] = "HEYD?KJS";

	ft_striteri(str, ft_test);
	printf("%s", str);
	return (0);
}*/