/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/09 17:50:07 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	is_builtin(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"pwd")
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, cmd, "unset")
		|| !ft_strcmp(cmd, cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
} */
/* int exec_builtin(char **split, int *exit_status)
{
	if (!ft_strcmp(split[0], "echo"))
		return (ft_echo(split));
	else if (!ft_strcmp(split[0], "cd"))
		return (ft_cd(split));
	else if (!ft_strcmp(split[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(split[0], "export"))
		return (ft_export(split));
	else if (!ft_strcmp(split[0], "unset"))
		return (ft_unset(split));
	else if (!ft_strcmp(split[0], "env"))
		return (ft_env(split));
	else if (!ft_strcmp(split[0], "exit"))
		return (ft_exit(split, exit_status));
	return (1);
} */
void	free_split(char **split)
{
	int	i;
	
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_struct(t_env *env)
{
	t_env *tmp;

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

int	main(int ac, char **av, char **envp)
{
	char	**split;
	t_env	*env;

	split = NULL;
	(void)ac;
	split = ft_split(av[1], ' ');
	if (!split || !split[0])
		return (1);
	env = init_env(envp);
	// print_list(env);
	if (ft_cd(split, env) == 1)
	{
		printf("CD FAILED\n");
		free_struct(env);
		free_split(split);
		return (-1);
	}
	free_split(split);
	free_struct(env);
	return (0);
}
