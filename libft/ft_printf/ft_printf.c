/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:03:14 by ocviller          #+#    #+#             */
/*   Updated: 2025/06/05 12:25:57 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count += ft_printnb(va_arg(args, int));
	else if (c == 'u')
		count += ft_printuns(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_printhex(va_arg(args, unsigned int));
	else if (c == 'X')
		count += ft_printhex_up(va_arg(args, unsigned int));
	else if (c == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (c == 'c')
		count += ft_printchar(va_arg(args, int));
	else if (c == '%')
		count += ft_printchar('%');
	else if (c == 'p')
		count += ft_printmem(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	args;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_format(format[i], args);
		}
		else
			count += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
