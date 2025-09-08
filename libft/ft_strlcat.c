/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:18:45 by ocviller          #+#    #+#             */
/*   Updated: 2025/04/27 17:48:45 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	srclen;
	size_t	destlen;

	i = 0;
	srclen = ft_strlen(src);
	destlen = ft_strlen(dst);
	if (destlen >= siz)
		return (siz + srclen);
	while (src[i] != '\0' && (i + destlen) < siz - 1)
	{
		dst[i + destlen] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
