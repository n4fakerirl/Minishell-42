/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:47 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 21:06:43 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char *str;
	t_token *tokens;
	t_cmd *test;
	t_cmd *cmds;

	(void)av;
	(void)ac;
	int i;
	int y = 0;
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		tokens = tokenize(str);
		new_type(tokens);
		cmds = NULL;
		trim_words(tokens);
		cmd_list(tokens, &cmds);
		test = cmds;
		while (test != NULL)
		{
			i = 0;
			while (test->args[i])
			{
				printf("CMD[%d]: %s\n", y, test->args[i]);
				i++;
			}
			test = test->next;
			y++;
		}
	}
	return (0);
}