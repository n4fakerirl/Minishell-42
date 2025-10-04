/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 14:23:19 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char *str;
	//int	exit_status;
	t_shell	*shell;
	
	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		shell = start_parsing(str, envp);
		shell->nbr_cmd = count_list(shell->cmd);
		start_exec(shell);
		free(str);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}
