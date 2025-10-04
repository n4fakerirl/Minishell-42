/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:09:13 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:58:16 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*pre_conv(int len)
{
	char	*tmp;

	tmp = ft_calloc((len + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '0';
	return (tmp);
}

static int	count_int(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{	
		count++;
		n = -n;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;
	long	nbr;

	nbr = n;
	len = count_int(nbr);
	res = pre_conv(len);
	if (!res)
		return (NULL);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		res[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}

/*int	main(void)
{
	int	n;

	n = 0;
	printf("%s", ft_itoa(n));
	return (0);
}*/