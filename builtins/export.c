/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:32:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/12 10:39:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	ft_cherche(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
} */

int	check_node(char *str, t_env *env)
{
	char	*true_key;
	char	*tmp;

	tmp = ft_strchr(str, '=');
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);
	else
		true_key = ft_strdup(str);
	while (env)
	{
		if (!ft_strcmp(true_key, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

void	print_export(t_env *env, bool egal)
{
	while (env)
	{
		printf("export ");
		if (!env->value && !egal)
			printf("%s\n", env->key);
		else 
			printf("%s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void	replace_value(char *str, t_env *env)
{
	char	*new_value;
	char	*true_key;
	char	*tmp;

	tmp = ft_strchr(str, '=');
	new_value = tmp + 1;
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);
	else
		true_key = ft_strdup(str);
	while (env)
	{
		if (!ft_strcmp(true_key, env->key))
			env->value = ft_strdup(new_value);
		env = env->next;
	}
}

int	check_var(char *str)
{
	int	i;
	char	*true_key;
	char	*tmp = NULL;

	i = 0;
	tmp = ft_strchr(str, '=');
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);	
	else
		true_key = str;
	if (!true_key || !true_key[0])
		return (1);
	if (!(ft_isalpha(true_key[0]) || true_key[0] == '_'))
		return (1);
	i++;
	while (true_key[i])
	{
		if (!(ft_isalnum(true_key[i]) || true_key[i] == '_'))
			return (1);
		i++;	
	}
	return (0);
}

int	ft_export(char **split, t_env *env, int *exit_code)
{
	int		i;
	t_env	*tmp;
	t_env	*new;
	bool	egal = false;

	tmp = env;
	new = NULL;
	i = 0;
	while (split[i])
		i++;
	if (i == 1)
	{
		print_export(env, false);
		return (0);
	}
	i = 0;
	while (split[++i])
	{
		if (check_var(split[i]))
		{
			printf("minishell: export: \'%s\': not a valid identifier\n", split[i]);
			*exit_code = 1;
			continue;
		}
		else if (!ft_strchr(split[i], '='))
		{
			if (check_node(split[i], env) == 1)
				;
			else
			{
				new = env_conv(split[i]);
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = new;
			}
		}
		else
		{
			if (check_node(split[i], env) == 1)
			{
				egal = true;
				replace_value(split[i], env);
			}
			else
			{
				egal = true;
				new = env_conv(split[i]);
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = new;
			}
		}
	}
	return (1);
}

