/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:47 by ocviller          #+#    #+#             */
/*   Updated: 2025/10/03 17:35:06 by ocviller         ###   ########.fr       */
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
	t_redir *redirs;

	(void)av;
	(void)ac;
	env = NULL;
	redirs = NULL;
	env = init_env(envp);
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		if (!str)
			break ;
		tokens = tokenize(str);
		new_type(tokens);
		parse_args(tokens);
		cmds = NULL;
		need_expand(tokens);
		trim_words(tokens);
		cmd_list(tokens, &cmds, env, redirs);
		test = cmds;
		t_token *tmp = tokens;
		printf("---TOKENS---\n");
		while (tmp)
		{
			printf("VALUE : %s | TYPE %d\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
		printf("---FIN---\n");
		while (test)
		{
			int i = 0;
			printf("\ncmd[]\n");
			while (test->args[i])
			{
				printf("%s ", test->args[i]);
				i++;
			}
			printf("\nREDIR\n");
			if (test->redir)
			{
				while (test->redir)
				{
					printf("TYPE : %d | FILE : %s\n", test->redir->type, test->redir->file);
					test->redir = test->redir->next;
				}
			}
			test = test->next;
		}
	}
	return (0);
}
