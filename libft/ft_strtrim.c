/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:16:49 by ocviller          #+#    #+#             */
/*   Updated: 2025/05/05 16:10:11 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_sep(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*dest;

	start = 0;
	end = ft_strlen(s1);
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && check_sep(s1[start], set))
		start++;
	while (end > start && check_sep(s1[end - 1], set))
		end--;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = s1[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
