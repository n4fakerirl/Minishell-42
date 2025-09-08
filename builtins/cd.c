/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:09:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/08 21:42:40 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(t_env *env, char *pwd)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, pwd))
			return (ft_strdup(env->value));
		else
			env = env->next;
	}
	return (NULL);
}

void	maj_pwd(t_env *env, char *pwd, char *old_path)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, pwd))
		{
			free(env->value);
			env->value = ft_strdup(old_path);
			return ;
		}
		env = env->next;
	}
}

void	change_directory(t_env *env, char *path)
{
	char	*current_pwd;
	char	*new_pwd;
	
	current_pwd = get_pwd(env, "PWD");
	if (chdir(path) < 0 || access(NULL, X_OK))
	{
		printf("ERROR\n");
		free(current_pwd);
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	maj_pwd(env, "OLDPWD", current_pwd);
	maj_pwd(env, "PWD", new_pwd);
	free(new_pwd);
	free(current_pwd);
}

int	ft_cd(char **split, t_env *env)
{
	char	*path;
	
	if (!split[1] || !split[1][0] || !ft_strcmp(split[1], "~") || !ft_strcmp(split[1], "--"))
	{	
		path = get_pwd(env, "HOME");
		if (!path)
		{
			perror("cd");
			return (-1);
		}
		change_directory(env, path);
		free(path);
	}
	else if (!ft_strcmp(split[1], "-"))
	{
		path = get_pwd(env, "OLDPWD");
		if (!path)
		{
			perror("cd");
			return (-1);
		}
		change_directory(env, path);
		printf("%s\n", path);
		free(path);
	}
	else if (split[1])
		change_directory(env, split[1]);
	return (0);
}
