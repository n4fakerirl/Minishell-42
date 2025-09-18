/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:56:48 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/18 04:32:08 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = ft_strlen(s1);
	destlen = ft_strlen(s2);
	i = 0;
	join = malloc(sizeof(char) * (srclen + destlen + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		join[srclen + i] = s2[i];
		i++;
	}
	join[srclen + i] = '\0';
	return (join);
}
