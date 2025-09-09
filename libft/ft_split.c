/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/09 15:46:54 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
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
	size_t	len;

	len = ft_strlen(s);
	ft_initialize(&i, &j, &s_word);
	if (!s || !*s)
		return (NULL);
	arr = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < len)
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if (s[i] == c && s_word >= 0)
		{
			arr[j] = fill_word(s, s_word, i);
			if (!arr[j])
				return (ft_free(arr));
			s_word = -1;
			j++;
			arr[j] = 0;
		}
	}
	if (s_word >= 0)
	{
		arr[j] = fill_word(s, s_word, i);
		if (!arr[j])
			return (ft_free(arr));
		arr[j + 1] = 0;
	}
	return (arr);
}

/* int	main(int ac, char **av)
{
	char c;
	char **tab;
	int i;

	if (ac == 2 && av[1] && av[1][0])
	{
		c = ' ';
		i = 0;
		tab = ft_split(av[1], c);
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
		ft_free(tab);
	}
	else
	{
		printf("ERROR\n");
		return (-1);
	}
	return (0);
} */