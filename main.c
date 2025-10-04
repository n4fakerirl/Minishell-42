/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 19:12:12 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char *str;
	t_shell	*shell;
	int	exit_status;
	
	(void)av;
	exit_status = 0;
	if (ac != 1)
		return (1);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
		{
			printf("CTRL D\n");
			break ;
		}
		shell = start_parsing(str, envp, exit_status);
		if (!shell)
		{
			exit_status = 2;
			continue;
		}
		shell->nbr_cmd = count_list(shell->cmd);
		printf("exit status avant exec = %d\n", shell->exit_status);
		start_exec(shell);
		printf("exit status apres exec = %d\n", shell->exit_status);
		exit_status = shell->exit_status;
		free(str);
		free_shell(shell);
	}
	//rl_clear_history();
	return (0);
}
