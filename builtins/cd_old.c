/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:14:30 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/08 21:05:25 by lenakach         ###   ########.fr       */
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

void	go_to_oldpwd(t_env *env)
{
	char	*current_pwd = NULL;
	char	*old_pwd = NULL;
	t_env	*tmp;

	tmp = env;
	current_pwd = get_pwd(env, "PWD");
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{				
			old_pwd = ft_strdup(tmp->value);
			if (chdir(tmp->value) < 0)
			{
				printf("ERRUEUR CHDIR\n");
				return ;
			}
			else
			{	
				maj_pwd(env, "OLDPWD", current_pwd);
				maj_pwd(env, "PWD", old_pwd);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	go_to_home(t_env *env)
{
	char	*current_pwd = NULL;
	t_env	*tmp;
	
	tmp = env;
	current_pwd = get_pwd(env, "PWD");
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
		{
			if (chdir(tmp->value) < 0)
			{
				printf("ERREUR DE CHDIR VERS HOME\n");
				return ;
			}
			else
			{
				maj_pwd(env, "OLDPWD", current_pwd);
				maj_pwd(env, "PWD", tmp->value);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	go_to_pwd(t_env *env, char *str)
{
	char	*current_pwd = NULL;
	char	*new_pwd = NULL;

	new_pwd = getcwd(NULL, 0);
	current_pwd = get_pwd(env, "PWD");
	if (chdir(str) < 0)
	{
		printf("ERREUR DE CHDIR DANS CD PWD\n");
		return ;
	}
	maj_pwd(env, "OLDPWD", current_pwd);
	maj_pwd(env, "PWD", new_pwd);
	free(new_pwd);
}

int	ft_cd(char **split, t_env *env)
{
	if (!split[1] || !split[1][0] || !ft_strcmp(split[1], '--') || split[1] == '~')
	{
		go_to_home(env);
		return (0);
	}
	else if (ft_strncmp(split[1], "-", 1) == 0)
	{
		go_to_oldpwd(env);
		return (0);
	}
	else if (split[1])
	{
		go_to_pwd(env, split[1]);	
		return (0);
	}
	else
	{
		printf("ERREUR DARGS POUR CD\n");
		return (2);
	}
}
