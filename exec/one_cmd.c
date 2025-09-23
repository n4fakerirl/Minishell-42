/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/23 13:00:37 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_cmd(t_shell *shell, char **envp_initial)
{
	//shell->pipe_infos->pid[0] = fork();
	//if (shell->pipe_infos->pid[0] < 0)
	//{
	//	ft_putstr_fd("Error: fork failed\n", 2);
	//	shell->exit_status = 1;
	//	return ;
	//}
	//else if (shell->pipe_infos->pid[0] == 0)
	//{
	//int	exit_status;
	
	if (is_builtin(shell->cmd->args[0]))
	{
		printf("JE RENTRE DANS BUILTIN\n");
		shell->exit_status = exec_builtin(shell, &(shell->env));
		//exit_status = shell->exit_status;
		//free_shell(shell);
		//exit (exit_status);
	}
	else
			one_child(shell, envp_initial);
}

void	one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;

	shell->pipe_infos->pid[0] = fork();
	if (shell->pipe_infos->pid[0] < 0)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (shell->pipe_infos->pid[0] == 0)
	{
		cmd_finale = get_cmd(shell);
		if (!cmd_finale)
		{
			printf("bash: %s: command not found\n", shell->cmd->args[0]);
			shell->exit_status = 127;
			return ;
		}
		if (execve(cmd_finale, shell->cmd->args, envp_initial))
		{
			perror("execve");
			free(cmd_finale);
			exit (127);
		}
	}
}
