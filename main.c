/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:42:51 by ocviller          #+#    #+#             */
/*   Updated: 2025/09/10 20:37:09 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;
	t_token	*tokens;
	t_cmd	*test;
	t_cmd	*cmds;
	int		i;

	test = malloc(sizeof(t_cmd));
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (1);
	ft_bzero(cmds, sizeof(t_cmd));
	(void)av;
	(void)ac;
	i = 0;
	while (1)
	{
		str = readline("minishell$ ");
		tokens = tokenize(str);
		new_type(tokens);
		cmd_list(tokens, &cmds);
		test = cmds;
		while (test != NULL)
		{
			while (test->args[i])
			{
				printf("CMD : %s\n", test->args[i]);
				i++;
			}
			test = test->next;
		}
	}
}
