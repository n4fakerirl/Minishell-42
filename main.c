/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/13 21:12:03 by lenakach         ###   ########.fr       */
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

int exec_builtin(char **split, t_env **env)
{
	int	exit_flag;
	int	exit_code;

	exit_flag = 1;
	exit_code = 0;
	if (!ft_strcmp(split[0], "echo"))
		return (ft_echo(split));
	else if (!ft_strcmp(split[0], "cd"))
		return (ft_cd(split, env));
	else if (!ft_strcmp(split[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(split[0], "env"))
		return (ft_env(split, *env, false));
	else if (!ft_strcmp(split[0], "exit"))
	{
		exit_code = ft_exit(split, &exit_flag);
		if (exit_flag == 1)
			return (free_split(split), free_struct(*env), exit(exit_code), 0);
	}
	else if (!ft_strcmp(split[0], "export"))
		return (ft_export(split, env, &exit_code));
	else if (!ft_strcmp(split[0], "unset"))
		return(ft_unset(split, env));
	return (1);
}


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
		if (env)
			free(env);
		env = tmp;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		exit_status;
	char	**split;
	char	*line;

	(void)av;
	if (ac != 1)
		return (1);
	env = init_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		//if (*line)
		//	add_history(line);
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			continue;
		exit_status = exec_builtin(split, &env);
		free_split(split);
		printf("%d\n", exit_status);
	}
	//if (exit_status != 0)
	//	return (free_struct(env), exit_status);
	free_struct(env);
	//exit_status = exec_builtin((av + 1), &env);
	//ft_env(av + 1, env, true);
	return (0);
}
