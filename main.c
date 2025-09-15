/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/15 14:39:09 by lenakach         ###   ########.fr       */
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
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
} */

int exec_builtin(t_cmd *cmd, t_env **env, char **split)
{
	int	exit_flag;
	int	exit_code;

	exit_flag = 1;
	exit_code = 0;
	(void)env;
	if (!ft_strcmp(cmd->name, "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->name, "cd"))
		return (ft_cd(cmd->args, env));
	else if (!ft_strcmp(cmd->name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->name, "env"))
		return (ft_env(cmd->args, *env, false));
	else if (!ft_strcmp(cmd->name, "exit"))
	{
		exit_code = ft_exit(cmd->args, &exit_flag);
		if (exit_flag == 1)
		{
			printf("OK J EXITTTT\n\n");
			free_split(split);
			printf("%d\n", exit_code);
			return (free_cmd(cmd), free_env(*env), exit(exit_code), 0);
		}
	}
	else if (!ft_strcmp(cmd->name, "export"))
		return (ft_export(cmd->args, env, &exit_code));
	else if (!ft_strcmp(cmd->name, "unset"))
		return(ft_unset(cmd->args, env));
	return (1);
}

//Simulation parsing
t_cmd	*init_cmd(char **split)
{
	t_cmd	*new_cmd;
	int		i;
	int		j;
	int		len;

	len = 0;
	while (split[len])
		len++;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->name = ft_strdup(split[0]);
	if (!new_cmd->name)
	{
		free_cmd(new_cmd);
		return (NULL);
	}	
	new_cmd->args = malloc((len) *sizeof(char *));
	if (!new_cmd->args)
	{
		free_cmd(new_cmd);
		return (NULL);
	}	
	j = 0;
	i = 1;
	while (i < len)
	{
		new_cmd->args[j] = ft_strdup(split[i]);
		i++;
		j++;
	}
	new_cmd->args[j] = NULL;
	j = 0;
	return (new_cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		exit_status;
	char	**split;
	t_cmd	*cmd;
	char	*line;

	exit_status = 0;
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
		if (*line)
			add_history(line);
		split = ft_split(line, ' ');
		if (!split)
		{
			free(line);
			continue;
		}
		cmd = init_cmd(split);
		if (!cmd)
		{
			free(line);
			free_split(split);
			continue ;	
		}
		exit_status = exec_builtin(cmd, &env, split);
		free_cmd(cmd);
		free(line);
		free_split(split);
		rl_clear_history();
		printf("%d\n", exit_status);
	}
	if (exit_status != 0)
		return (free_env(env), exit_status);
	free_env(env);
	return (0);
}
