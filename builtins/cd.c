/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:09:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 18:21:16 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(t_env *env, char *pwd)
{
	char	*new_pwd;

	while (env != NULL)
	{
		if (!ft_strcmp(env->key, pwd))
		{
			new_pwd = ft_strdup(env->value);
			if (!new_pwd)
			{
				ft_putstr_fd("minishell: cd: malloc error\n", 2);
				return (NULL);
			}
			return (new_pwd);
		}
		else
			env = env->next;
	}
	return (NULL);
}

int	new_pwd(t_env **env, char *pwd)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = ft_strdup(pwd);
	if (!new->key)
		return (free(new), 0);
	new->value = NULL;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

void	maj_pwd(t_env *env, char *pwd, char *old_path)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, pwd))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(old_path);
			if (!env->value)
				ft_putstr_fd("minishell: cd: malloc error\n", 2);
		}
		env = env->next;
	}
}

int	change_directory(t_env *env, char *path)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		return (cwd_exit("minishell: cd: error retrieving current directory"),
			1);
	}
	if (chdir(path) == -1)
		return (chdir_exit("minishell: cd: ", path), free(current_pwd), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (cwd_exit("minishell: cd: "), free(current_pwd), 1);
	maj_pwd(env, "OLDPWD", current_pwd);
	maj_pwd(env, "PWD", new_pwd);
	free(new_pwd);
	free(current_pwd);
	return (0);
}

int	ft_cd(char **split, t_env *env)
{
	char	*path;

	if (!split[1] || !split[1][0] || !ft_strcmp(split[1], "~")
		|| !ft_strcmp(split[1], "--"))
	{
		path = get_pwd(env, "HOME");
		if (!path)
			return (getpwd_exit("minishell: cd: HOME not set\n"), 1);
		if (change_directory(env, path) == 1)
			return (free(path), 1);
		free(path);
	}
	else if (!ft_strcmp(split[1], "-"))
	{
		path = get_pwd(env, "OLDPWD");
		if (!path)
			return (getpwd_exit("minishell: cd: OLDPWD not set\n"), 1);
		if (change_directory(env, path) == 1)
			return (free(path), 1);
		return (printf("%s\n", path), free(path), 0);
	}
	else if (split[1])
		if (change_directory(env, split[1]) == 1)
			return (1);
	return (0);
}
