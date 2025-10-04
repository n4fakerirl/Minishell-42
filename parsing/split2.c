/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:09:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 23:06:30 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	separator(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		else
			charset++;
	}
	return (0);
}

int	len_words(char *str, char *charset)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (*str && separator(*str, charset))
			str++;
		if (*str)
			word++;
		while (*str && !separator(*str, charset))
			str++;
	}
	return (word);
}

char	*ft_strdup_sep(char *str, char *charset)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	i = 0;
	while (str[len] == '$' || str[len] == '\\')
		len++;
	while (str[len] && !separator(str[len], charset))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split_d(char *str, char *charset)
{
	int		words;
	int		i;
	char	**result;

	words = len_words(str, charset);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && separator(*str, charset))
			str++;
		if (*str)
		{
			if (*(str - 2) && *(str - 2) == '\\')
				result[i] = ft_strdup_sep(str - 2, charset);
			else if (*(str - 1) == '$')
				result[i] = ft_strdup_sep(str - 1, charset);
			else
				result[i] = ft_strdup_sep(str, charset);
			if (!result[i])
				return (NULL);
			i++;
		}
		while (*str && !separator(*str, charset))
			str++;
	}
	result[i] = NULL;
	return (result);
}
