/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:18:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 16:40:29 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_cmd(t_shell *shell, char **envp_initial)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork failed\n", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (pid == 0)
		one_child(shell, envp_initial);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 1;
	}
}

void	one_child(t_shell *shell, char **envp_initial)
{
	char	*cmd_finale;
	//g deja cmd_args rempli;
	cmd_finale = get_cmd(shell);
	if (!cmd_finale)
	{
		printf("bash: %s: command not found\n", shell->cmd->name);
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