/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/16 15:53:33 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (free_cmd(new_cmd), NULL);
	new_cmd->args = malloc((len) *sizeof(char *));
	if (!new_cmd->args)
		return (free_cmd(new_cmd), NULL);
	j = 0;
	i = 0;
	while (++i < len)
		new_cmd->args[j++] = ft_strdup(split[i]);
	new_cmd->args[j] = NULL;
	new_cmd->redirect = 0;
	new_cmd->here_doc = 0;
	return (new_cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*line;
	int	exit_status;

	(void)av;
	if (ac != 1)
		return (1);
	shell = init_shell(envp);
	if (!shell)
		return (1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			break;
		}
		if (*line)
			add_history(line);
		shell->av = ft_split(line, ' ');
		if (!shell->av)
		{
			free(line);
			continue;
		}
		shell->cmd = init_cmd(shell->av);
		if (!shell->cmd)
		{
			free(line);
			continue;
		}
		shell->exit_status = exec_builtin(shell, &(shell->env));
		free(line);
		free_cmd(shell->cmd);
		free_split(shell->av);
		printf("%d\n", shell->exit_status);
	}
	if (shell->exit_status != 0)
	{
		exit_status = shell->exit_status;
		shell->av = NULL;
		shell->cmd = NULL;
		free_shell(shell);
		return (exit_status);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}
