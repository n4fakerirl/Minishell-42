/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:58:00 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 17:00:20 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **split)
{
	int	i;
	
	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;

	if (!cmd)
		return;
	if (cmd->name)
		free(cmd->name);
	if (!cmd->args)
	{
		free(cmd);
		return ;
	}
	while (cmd->args[i])
	{
		if (cmd->args[i])
			free(cmd->args[i]);
		i++;
	}
	if (cmd->args)
		free(cmd->args);
	if (cmd)
		free(cmd);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		if (env)
			free(env);
		env = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->env)
		free_env(shell->env);
	if (shell->av)
		free_split(shell->av);
	if (shell->envp_initial)
		free_split(shell->envp_initial);
	free(shell);
}
