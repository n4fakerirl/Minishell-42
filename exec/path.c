/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:21:30 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/17 16:13:13 by lenakach         ###   ########.fr       */
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

	if (!shell->cmd->name)
	{
		printf("PAS DE COMMANDE\n");
		return (NULL);
	}
	if (access(shell->cmd->name, X_OK) == 0)
	{
		cmd_finale = ft_strdup(shell->cmd->name);
		if (!cmd_finale)
		{
			printf("strdup de cmd failed\n");
			return (NULL);
		}
		return (cmd_finale);
	}
	path_tmp = find_path(shell->env);
	if (!path_tmp)
	{
		printf("PAS TROUVE LE CHEMIN\n");
		return (NULL);
	}
	path = ft_split(path_tmp, ':');
	if (!path)
	{
		printf("SPLIT POUR AVOIR PATH ** FAILED\n");
		return (NULL);
	}
	cmd_finale = fill_path(path, shell->cmd->name);
	return (cmd_finale);
}