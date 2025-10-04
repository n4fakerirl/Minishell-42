/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:18:53 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 12:22:02 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*addspace(char **split, t_space *space)
{
	int		i;
	int		y;
	char	*tmp;
	char	*new_str;
	t_space	*current;

	i = 0;
	current = space;
	while (split[i])
	{
		if (current && current->space_nbr > 0)
		{
			y = 0;
			while (y < current->space_nbr)
			{
				printf("current space %d\n", space->space_nbr);
				tmp = ft_strjoin(split[i], " ");
				if (!tmp)
					return (NULL);
				free(split[i]);
				split[i] = ft_strdup(tmp);
				y++;
			}
		}
		i++;
		if (current)
			current = current->next;
	}
	tmp = ft_strdup(split[0]);
	if (!tmp)
		return (NULL);
	i = 1;
	while (split[i])
	{
		new_str = ft_strjoin(tmp, split[i]);
		free(tmp);
		if (!new_str)
			return (NULL);
		tmp = ft_strdup(new_str);
		i++;
	}
	return (tmp);
}

void	add_sp(t_space **spaces, t_space *space)
{
	t_space	*tmp;

	tmp = *spaces;
	if (!*spaces)
	{
		*spaces = space;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = space;
	space->next = NULL;
}

t_space	*create_sp(char *str, t_space *space)
{
	int		i;
	int		y;
	int		count;
	t_space	*tmp;

	i = 0;
	count = 0;
	tmp = malloc(sizeof(t_space));
	while (str[i])
	{
		y = 0;
		while (ft_isspace(str[i + y]) && str[i + y] != '\0')
			y++;
		if (y > 0)
		{
			tmp = malloc(sizeof(t_space));
			tmp->index = count++;
			tmp->space_nbr = y;
			add_sp(&space, tmp);
			i += y;
			continue ;
		}
		i++;
	}
	return (space);
}

int	put_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*del_back(t_token *token)
{
	int		len;
	char	*buf;
	int		i;
	int		j;

	j = 0;
	if (token->state == SINGLE_QUOTE)
		return (ft_strdup(token->value));
	len = ft_strlen(token->value);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\\')
		{
			i++;
			if (!token->value[i])
				break ;
			if (token->state == DOUBLE_QUOTE && backspecial(token->value[i]))
				buf[j++] = token->value[i];
			else
				buf[j++] = token->value[i];
		}
		else
			buf[j++] = token->value[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}
