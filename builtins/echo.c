/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:22 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 16:15:30 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int newlines(char **split, int *new_line, int i)
{
    int j;

    if (split[0] && !ft_strncmp(split[0], "-n", 2))
    {
        j = 2;
        while (split[0][j] && split[0][j] == 'n')
            j++;
        if (split[0][j] == '\0')
        {
            *new_line = 0;
            i++;
        }
    }
    while (split[i] && !ft_strncmp(split[i], "-n", 2))
    {
        j = 2;
        while (split[i][j] && split[i][j] == 'n')
            j++;
        if (split[i][j] == '\0')
            i++;
        else
            break ;
    }
    return (i);
}

int    ft_echo(char **split)
{
    int    new_line;
    int    i;
    int    j;

    i = 0;
    j = 0;
    new_line = 1;
    i = newlines(split, &new_line, 0);
    while (split[i])
    {
        write(STDOUT_FILENO, split[i], ft_strlen(split[i]));
        if (split[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (new_line)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
