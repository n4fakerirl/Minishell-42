/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:36:55 by ocviller          #+#    #+#             */
/*   Updated: 2025/06/05 12:24:50 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printmem(void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5), 5);
	write(1, "0x", 2);
	return (ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef") + 2);
}
