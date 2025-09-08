/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 14:34:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	**ft_free(char **arr, int j)
{
	while (j >= 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
	return (NULL);
}

static void	ft_initialize(size_t *i, int *j, int *s_word)
{
	*i = -1;
	*j = 0;
	*s_word = -1;
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;
	int		j;
	int		s_word;

	ft_initialize(&i, &j, &s_word);
	if (!s || !*s)
		return (NULL);
	arr = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			arr[j] = fill_word(s, s_word, i);
			if (!arr[j])
				return (ft_free(arr, j));
			s_word = -1;
			j++;
		}
	}
	return (arr);
}

/* int	main(void)
{
	const char	*s = "lorem ipsum";
	char		c;
	char		**tab;
	int			i;

	c = ' ';
	i = 0;
	tab = ft_split(s, c);
	printf("%d", word_count(s, c));
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
} */