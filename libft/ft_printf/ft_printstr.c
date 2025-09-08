/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:01:11 by ocviller          #+#    #+#             */
/*   Updated: 2025/06/04 10:23:34 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *str)
{
	int		count;

	count = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}
