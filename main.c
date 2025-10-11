/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/11 12:52:35 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_shell	*shell;
	int		exit_status;

	(void)av;
	if (ac != 1)
		return (1);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	ft_bzero(shell, sizeof(t_shell));
	shell->env = init_env(envp);
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
		start_parsing(str, envp, exit_status, shell);
		if (!shell)
		{
			exit_status = 2;
			free(str);
			continue ;
		}
		shell->nbr_cmd = count_list(shell->cmd);
		start_exec(shell);
		exit_status = shell->exit_status;
		free(str);
		free_shell(shell);
	}
	return (0);
}
