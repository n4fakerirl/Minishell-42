/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:58:00 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 13:50:50 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **split)
{
	int	i;
	
	i = 0;
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
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd)
		free(cmd);
}

void	free_env(t_env *env)
{
	t_env *tmp;

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
