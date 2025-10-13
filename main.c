/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 11:26:39 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_shell	*shell;
	int		exit_status;
	t_env	*tmp;
	int	first;

	first = 0;
	tmp = NULL;
	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell> ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		exit_status = 0;
		if (g_signal == SIGINT)
		{
			exit_status = 130;
			g_signal = 0;
		}
		if (!*str)
		{
			free(str);
			continue ;
		}
		shell = init_shell(envp, exit_status, first, tmp);
		if (!start_parsing(str, exit_status, shell) || !shell)
		{
			exit_status = 2;
			free(str);
			continue ;
			
		}
		shell->nbr_cmd = count_list(shell->cmd);
		start_exec(shell);
		exit_status = shell->exit_status;
		tmp = ft_env_dup(shell->env);
		free(str);
		free_shell(shell);
		if (first == 0)
			first = 1;
	}
	free_env(tmp);
	return (0);
}
