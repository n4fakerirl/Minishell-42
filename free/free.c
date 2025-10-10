/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:49:33 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/10 12:38:27 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*next;

	tmp = redir;
	if (!redir)
		return ;
	while (tmp)
	{
		if (tmp->file)
			free(tmp->file);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_redir(tmp->redirect);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp_initial)
		free_split(shell->envp_initial);
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->env)
		free_env(shell->env);
	if (shell->pipe_infos)
		free(shell->pipe_infos);
	free(shell);
}
