/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:58:00 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/22 17:28:19 by lenakach         ###   ########.fr       */
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
	t_cmd	*tmp;
	t_cmd	*next;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		fprintf(stderr, "FREE CMD (PID=%d)\n", getpid());
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_move_cmd(t_cmd *cmd)
{
	int		i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
}

/* void	free_cmd(t_cmd *cmd)
{
	int	i;
	t_cmd	*tmp;

	i = 0;

	if (!cmd)
		return;
	fprintf(stderr,"HEYYYY MON PID POUR FREE CMD EST : %d\n", getpid());
	tmp = cmd;		
	while (tmp)
	{
		i = 0;
		fprintf(stderr, "FREE CMD \n");
		if (!tmp->args)
		{
			free(tmp);
			 ;
		}
		while (tmp->args[i])
		{
			if (tmp->args[i])
				free(tmp->args[i]);
			i++;
		}
		if (tmp->args)
			free(tmp->args);
		tmp = tmp->next;
	}
	if (cmd)
		free(cmd);
} */

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
	if (!shell)
		return ;
	if (shell->cmd)
	{
		fprintf(stderr, "MA COMMANDE N'EST PAS NULL DONC JE FREE\n");
		free_cmd(shell->cmd);
	}
	if (shell->line)
		free(shell->line);
	if (shell->env)
		free_env(shell->env);
	if (shell->av)
		free_split(shell->av);
	if (shell->envp_initial)
		free_split(shell->envp_initial);
	if (shell->pipe_infos)
		free(shell->pipe_infos);
	free(shell);
}
