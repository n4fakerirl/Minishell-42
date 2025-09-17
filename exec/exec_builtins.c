/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:58:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 16:04:24 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_env **env)
{
	int	exit_flag;
	int	exit_code;

	exit_flag = 1;
	exit_code = 0;
	if (!ft_strcmp(shell->cmd->name, "echo"))
		return (ft_echo(shell->cmd->args));
	else if (!ft_strcmp(shell->cmd->name, "cd"))
		return (ft_cd(shell->cmd->args, env));
	else if (!ft_strcmp(shell->cmd->name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(shell->cmd->name, "env"))
		return (ft_env(shell->cmd->args, *env, false));
	else if (!ft_strcmp(shell->cmd->name, "exit"))
	{
		exit_code = ft_exit(shell->cmd->args, &exit_flag);
		if (exit_flag == 1)
			return (free_shell(shell), exit(exit_code), 0);
	}
	else if (!ft_strcmp(shell->cmd->name, "export"))
		return (ft_export(shell->cmd->args, env, &exit_code));
	else if (!ft_strcmp(shell->cmd->name, "unset"))
		return (ft_unset(shell->cmd->args, env));
	return (1);
}
