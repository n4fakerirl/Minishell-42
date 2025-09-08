/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:09:01 by ocviller          #+#    #+#             */
/*   Updated: 2025/06/04 10:23:37 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_unsigned(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

void	ft_putnbr_uns(unsigned int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr_uns(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	ft_printuns(unsigned int uns)
{
	int				count;

	count = ft_count_unsigned(uns);
	ft_putnbr_uns(uns);
	return (count);
}
