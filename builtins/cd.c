/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:09:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/09 20:32:19 by lenakach         ###   ########.fr       */
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
				fprintf(stderr, "minishell: cd: malloc error\n");
				return (NULL);
			}
			return (new_pwd);
		}
		else
			env = env->next;
	}
	return (NULL);
}

int	maj_pwd(t_env *env, char *pwd, char *old_path)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, pwd))
		{
			free(env->value);
			env->value = ft_strdup(old_path);
			if (!env->value)
			{
				fprintf(stderr, "minishell: cd: malloc error\n");
				return (1);
			}
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	change_directory(t_env *env, char *path)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		fprintf(stderr, "minishell: cd: error retrieving current directory: %s\n", strerror(errno));
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd:", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(":", 2);
		perror("");
		free(current_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		fprintf(stderr, "minishell: cd: error retrieving current directory: %s\n", strerror(errno));
		return (1);
	}
	if (maj_pwd(env, "OLDPWD", current_pwd) == 1)
	{
		free(current_pwd);
		free(new_pwd);
		return (1);
	}
	if (maj_pwd(env, "PWD", new_pwd) == 1)
	{
		free(current_pwd);
		free(new_pwd);
		return (1);
	}
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
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
		if (change_directory(env, path) == 1)
		{
			free(path);
			return (1);
		}
		free(path);
	}
	else if (!ft_strcmp(split[1], "-"))
	{
		path = get_pwd(env, "OLDPWD");
		if (!path)
		{
			fprintf(stderr, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
		if (change_directory(env, path) == 1)
		{
			free(path);
			return (1);
		}
		printf("%s\n", path);
		free(path);
	}
	else if (split[1])
		if (change_directory(env, split[1]) == 1)
			return (1);
	return (0);
}
