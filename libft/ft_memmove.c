/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:18:10 by ocviller          #+#    #+#             */
/*   Updated: 2025/04/30 17:48:17 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*dst;

	source = (unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!dest && !src)
		return (0);
	if (dest <= src)
	{
		while (n--)
			*dst++ = *source++;
	}
	else if (src < dest)
	{
		source = source + n - 1;
		dst = dst + n - 1;
		while (n--)
			*dst-- = *source--;
	}
	return (dest);
}
