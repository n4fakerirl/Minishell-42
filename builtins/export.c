/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:32:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/15 19:45:42 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_node(char *str, t_env *env)
{
	char	*true_key;
	char	*tmp;

	tmp = ft_strchr(str, '=');
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);
	else
	{
		true_key = ft_strdup(str);
		if (!true_key)
			return (1);
	}
	while (env)
	{
		if (!ft_strcmp(true_key, env->key))
		{
			free(true_key);
			return (1);
		}
		env = env->next;
	}
	free(true_key);
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

void	replace_value(char *str, t_env **env)
{
	char	*new_value;
	char	*true_key;
	char	*tmp;
	t_env	*curr;

	curr = *env;
	tmp = ft_strchr(str, '=');
	new_value = tmp + 1;
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);
	else
		true_key = ft_strdup(str);
	if (!true_key)
		return ;
	while (curr)
	{
		if (!ft_strcmp(true_key, curr->key))
		{
			free(curr->value);
			curr->value = ft_strdup(new_value);
			free(true_key);
			return ;
		}
		curr = curr->next;
	}
}

int	check_var(char *str)
{
	int		i;
	char	*true_key;
	char	*tmp;

	true_key = NULL;
	tmp = NULL;
	i = 0;
	tmp = ft_strchr(str, '=');
	if (tmp)
		true_key = ft_substr(str, 0, tmp - str);
	else
		true_key = ft_strdup(str);
	if (!true_key || !true_key[0] || !(ft_isalpha(true_key[0])
			|| true_key[0] == '_'))
	{
		if (true_key)
			free(true_key);
		return (1);
	}
	while (true_key[++i])
		if (!(ft_isalnum(true_key[i]) || true_key[i] == '_'))
			return (free(true_key), 1);
	return (free(true_key), 0);
}

void print_exp_err(char *message)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

int	ft_export(char **split, t_env **env, int *exit_code)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i == 0)
		return (print_export(*env, false), 0);
	i = -1;
	while (split[++i])
	{
		if (check_var(split[i]))
		{
			print_exp_err(split[i]);
			*exit_code = 1;
			continue ;
		}
		if (!ft_strchr(split[i], '=') && !check_node(split[i], *env))
			new_node(env, split[i]);
		else if (ft_strchr(split[i], '=') && check_node(split[i], *env) == 1)
			replace_value(split[i], env);
		else if (!check_node(split[i], *env))
			new_node(env, split[i]);
	}
	return (*exit_code);
}
