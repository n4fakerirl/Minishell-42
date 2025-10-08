/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:21:30 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/08 18:53:59 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(t_env *env)
{
	char	*result_path;

	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			result_path = ft_strdup(env->value);
			return (result_path);
		}
		env = env->next;
	}
	return (NULL);
}

char	*fill_path(char **path, char *cmd)
{
	char	*tmp;
	char	*cmd_finale;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_finale = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_finale)
			return (NULL);
		if (access(cmd_finale, X_OK) == 0)
		{
			free_split(path);
			return (cmd_finale);
		}
		free(cmd_finale);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*get_cmd(t_shell *shell)
{
	char	**path;
	char	*path_tmp;
	char	*cmd_finale;

	path = NULL;
	path_tmp = NULL;
	cmd_finale = NULL;
	if (!shell->cmd->args[0])
		return (NULL);
	if (access(shell->cmd->args[0], X_OK) == 0)
	{
		cmd_finale = ft_strdup(shell->cmd->args[0]);
		if (!cmd_finale)
			return (NULL);
		return (cmd_finale);
	}
	path_tmp = find_path(shell->env);
	if (!path_tmp)
		return (free(cmd_finale), NULL);
	path = ft_split(path_tmp, ':');
	if (!path)
		return (free(cmd_finale), free(path_tmp), NULL);
	cmd_finale = fill_path(path, shell->cmd->args[0]);
	free(path_tmp);
	return (cmd_finale);
}
