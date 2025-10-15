/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:19:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 17:57:40 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_node(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	new = env_conv(str);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_pipe	*init_pipe(void)
{
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
		return (error_malloc(), NULL);
	new_pipe->nbr_pipe = 0;
	return (new_pipe);
}

t_shell	*fill_shell(int exit_status)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (error_malloc(), NULL);
	shell->nbr_cmd = 0;
	shell->exit_status = exit_status;
	shell->saved_stdin = 0;
	shell->heredoc_interrupted = 0;
	shell->head_cmd = NULL;
	shell->saved_stdout = 0;
	shell->cmd = NULL;
	shell->pipe_infos = init_pipe();
	shell->envp_initial = 0;
	return (shell);
}

t_shell	*init_shell(char **envp, int exit_status, int first, t_env *tmp_env)
{
	t_shell	*new_shell;

	new_shell = fill_shell(exit_status);
	if (!new_shell)
		return (NULL);
	if (first == 0 || (first != 0 && !tmp_env))
	{
		new_shell->env = init_env(envp);
		if (!new_shell->env)
			return (free_shell(new_shell), NULL);
	}
	else if (first != 0 && tmp_env)
	{
		new_shell->env = ft_env_dup(tmp_env);
		if (!new_shell->env)
			return (free_shell(new_shell), NULL);
	}
	new_shell->envp_initial = dup_split(envp);
	if (!new_shell->envp_initial)
		return (free_shell(new_shell), NULL);
	if (!new_shell->env)
		return (free_shell(new_shell), NULL);
	return (new_shell);
}
