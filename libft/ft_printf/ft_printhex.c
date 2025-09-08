/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:04:02 by ocviller          #+#    #+#             */
/*   Updated: 2025/06/05 12:24:17 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long long nb, char *base)
{
	unsigned long long	nbr;
	char				result;
	int					count;

	nbr = nb;
	count = 0;
	if (nbr >= 16)
	{
		count += ft_putnbr_base(nbr / 16, base);
		count += ft_putnbr_base(nbr % 16, base);
	}
	if (nbr < 16)
	{
		count++;
		result = base[nbr];
		ft_putchar_fd(result, 1);
	}
	return (count);
}

int	ft_printhex(unsigned int nb)
{
	int	count;

	count = ft_putnbr_base(nb, "0123456789abcdef");
	return (count);
}

int	ft_printhex_up(unsigned int nb)
{
	int				count;

	count = ft_putnbr_base(nb, "0123456789ABCDEF");
	return (count);
}
