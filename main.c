/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:42:51 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/08 15:06:43 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;
	t_token	*tokens;

	tokens = malloc(sizeof(t_token **));
	if (!tokens)
		return (1);
	(void)av;
	(void)ac;
	str = readline("minishell$ ");
	tokens = tokenize(str);
	while (tokens != NULL)
	{
	    printf("TYPE : %d, CONTENT : %s\n", tokens->type, tokens->value);
	    tokens = tokens->next;
    }
}
