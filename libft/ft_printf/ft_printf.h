/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:33:23 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/02 16:05:42 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "../libft.h"

int	ft_printf(const char *format, ...);
int	ft_printchar(char c);
int	ft_printnb(int nb);
int	ft_printstr(char *str);
int	ft_printuns(unsigned int nb);
int	ft_printhex(unsigned int nb);
int	ft_printhex_up(unsigned int nb);
int	ft_putnbr_base(unsigned long long nb, char *base);
int	ft_printmem(void *ptr);
int	ft_print_pointer(void *ptr);

#endif