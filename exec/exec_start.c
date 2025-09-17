/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:29:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 18:48:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe++;	
		i++;
	}
	return (pipe);
}

int	start_exec(t_shell *shell)
{
	shell->pipe_infos->nbr_pipes = count_pipe(shell->line);
	if (!shell->pipe_infos->nbr_pipes)
	{
		one_cmd(shell, shell->envp_initial);
		return (shell->exit_status);
	}
	else
	{
		printf("MERDE %d\n", shell->pipe_infos->nbr_pipes);
		if (shell->pipe_infos->nbr_pipes == 1)
		{
			printf("FAIRE FIRST AND LAST\n");
			one_pipe(shell);
		}
		else
			printf("FIARE PIPEX BONUS COMPLET\n");
		return (shell->exit_status);
	}
}
