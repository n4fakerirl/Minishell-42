/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/04 14:52:46 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*line;
	int	exit_status;
	int	i;
	int	is_cmd;

	is_cmd = 1;
	(void)av;
	i = 0;
	if (ac != 1)
		return (1);
	shell = init_shell(envp);
	if (!shell)
		return (1);
	while (1)
	{
		i = 0;
		line = readline("minishell> ");
		if (!line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			shell->line = NULL;
			printf("CTRL D\n");
			break;
		}
		if (*line)
			add_history(line);
		shell->line = ft_strdup(line);
		shell->av = ft_split(line, ' ');
		shell->cmd = init_cmd(shell->av);
		//change_redir(shell->cmd);
		shell->nbr_cmd = count_list(shell->cmd);
		print_cmd(shell->cmd);
		start_exec(shell);
		free(line);
		free_cmd(shell->cmd);
		free_split(shell->av);
		free(shell->line);
	}
	if (shell->exit_status != 0)
	{
		exit_status = shell->exit_status;
		shell->av = NULL;
		shell->cmd = NULL;
		shell->line = NULL;
		free_shell(shell);
		return (exit_status);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}

