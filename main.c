/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:47 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/12 15:44:49 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av)
// {
// 	char *str;
// 	t_token *tokens;
// 	t_cmd *cmds;

// 	(void)av;
// 	(void)ac;
// 	while (1)
// 	{
// 		str = readline("minishell$ ");
// 		if (!str)
// 			break ;
// 		tokens = tokenize(str);
// 		new_type(tokens);
// 		cmds = NULL;
// 		trim_words(tokens);
// 		cmd_list(tokens, &cmds);
// 		parse_args(tokens);
// 	}
// 	return (0);
// }

int	main(int ac, char **av)
{
	char *str;
	t_token *tokens;
	t_cmd *cmds;
	t_token *test;

	(void)av;
	(void)ac;
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		tokens = tokenize(str);
		new_type(tokens);
		test = tokens;
		cmds = NULL;
		trim_words(tokens);
		cmd_list(tokens, &cmds);
		while (test)
		{
			printf("CMD : %s\n", test->value);
			test = test->next;
		}
		parse_args(tokens);
	}
	return (0);
}