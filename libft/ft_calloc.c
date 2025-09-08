/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:15:01 by ocviller          #+#    #+#             */
/*   Updated: 2025/05/05 16:45:54 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	void			*array;
	unsigned char	*str;

	i = 0;
	array = malloc(size * nmemb);
	str = array;
	if (!array)
		return (NULL);
	while (i < (nmemb * size))
	{
		str[i] = 0;
		i++;
	}
	return (array);
}
