/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:42:51 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 14:05:37 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;
	t_token	*tokens;
	t_token *token1 = malloc(sizeof(t_token));
	
	(void)av;
	(void)ac;
	while (1)
	{
		str = readline("minishell$ ");
		tokens = tokenize(str);
		new_type(tokens);
		token1 = tokens;
		while (token1 != NULL)
		{
			printf("TYPE : %d, CONTENT : %s\n", token1->type, token1->value);
			token1 = token1->next;
		}
	}
}
