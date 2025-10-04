/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:35:29 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/01 17:38:50 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3 || !s2)
		return (NULL);
	while (s1[i])
	{
		s3[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		s3[j] = s2[i];
		i++;
		j++;
	}
	s3[j] = '\0';
	return (s3);
}

/*int	main(void)
{
	const char	s1[] = "Hey";
	const char	s2[] = "Salut";

	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/
