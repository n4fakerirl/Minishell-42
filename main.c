/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:47 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/29 11:24:24 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av)
// {
// 	char *str;
// 	t_token *tokens;
// 	t_token *tmp;

// 	(void)av;
// 	(void)ac;
// 	while (1)
// 	{
// 		str = readline("minishell$ ");
// 		if (!str)
// 			break ;
// 		tokens = tokenize(str);
// 		new_type(tokens);
// 		//parse_args(tokens);
// 		//need_expand(tokens);
// 		//trim_words(tokens);
// 		tmp = tokens;
// 		while (tmp)
// 		{
// 			printf("token[] : %s\n", tmp->value);
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	char *str;
	t_token *tokens;
	t_cmd *cmds;
	t_cmd *test;
	t_env *env;

	(void)av;
	(void)ac;
	env = NULL;
	env = init_env(envp);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		tokens = tokenize(str);
		new_type(tokens);
		parse_args(tokens);
		cmds = NULL;
		need_expand(tokens);
		trim_words(tokens);
		cmd_list(tokens, &cmds, env);
		test = cmds;
		while (test)
		{
			int i = 0;
			printf("cmd[] : ");
			while (test->args[i])
			{
				printf("%s ", test->args[i]);
				i++;
			}
			printf("\n");
			test = test->next;
		}
	}
	return (0);
}
