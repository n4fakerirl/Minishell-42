/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:13:04 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 12:55:12 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c)
		count++;
	while (s[i])
	{
		if (i > 0 && s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static char	*malloc_word(const char *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

void	ft_free(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}

static char	**ft_ft(char const *s, char c, char **result)
{
	int	i;
	int	y;
	int	len;

	i = 0;
	y = 0;
	while (s[i])
	{
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len > 0)
		{
			result[y] = malloc_word(s + i, len);
			if (!result[y])
				return (ft_free(result), NULL);
			y++;
		}
		if (s[i] == c)
			i++;
		i += len;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;

	count = count_words(s, c);
	if (s[0] == '\0')
	{
		result = malloc(sizeof(char *) * 1);
		if (!result)
			return (NULL);
		return (result[0] = NULL, result);
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result = ft_ft(s, c, result);
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
