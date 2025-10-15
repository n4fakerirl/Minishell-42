/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:34:01 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 18:17:10 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (error_malloc(), NULL);
	else
		return (ft_strcpy(dest, s));
}
/*int	main(void)
{
	const char	str[] = "Heydkjb124";

	printf("ma chaine source avant : %s\n", str);
	printf("Ma chaine dest apres : %s", ft_strdup(str));
	return (0);
}*/