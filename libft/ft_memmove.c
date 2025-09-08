/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:07:03 by lenakach          #+#    #+#             */
/*   Updated: 2025/07/21 13:59:18 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (n == 0 || dest == src)
		return (dest);
	if (d > s && d < s + n)
		while (n--)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char test1[] = "ABCDEFGHIJ";
    char test2[] = "ABCDEFGHIJ";

    // 🧪 Test sans chevauchement (copie normale)
    printf("Avant (sans chevauchement) : %s\n", test1);
    ft_memmove(test1 + 5, test1, 5);  // 
	Copie les 5 premiers caractères à partir de l'indice 5
    printf("Après  (sans chevauchement) : %s\n", test1);

    // 🧪 Test avec chevauchement (copie vers la droite)
    printf("\nAvant (avec chevauchement) : %s\n", test2);
    ft_memmove(test2 + 2, test2, 8);  // Les zones se chevauchent
    printf("Après  (avec chevauchement) : %s\n", test2);

    // 🧪 Test dans l'autre sens (copie vers la gauche)
    char test3[] = "1234567890";
    printf("\nAvant (copie vers gauche) : %s\n", test3);
    ft_memmove(test3, test3 + 2, 8);  // 
	Copie 8 caractères en avançant dans la zone
    printf("Après  (copie vers gauche) : %s\n", test3);

    return 0;
}*/