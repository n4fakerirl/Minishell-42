/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/13 19:04:36 by ocviller ### ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_sigint(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->exit_status = 130;
		g_signal = 0;
	}
}

void	end_shell(t_shell *shell, t_env **tmp, char *str, t_data *data)
{
	shell->nbr_cmd = count_list(shell->cmd);
	shell->data = data;
	start_exec(shell);
	*tmp = ft_env_dup(shell->env);
	data->exit_status = shell->exit_status;
	free(str);
	if (data->first == 0)
		data->first = 1;
}

t_shell	*shell_parsing(char **envp, t_data *data, char *str, t_env **tmp)
{
	t_shell	*shell;

	shell = init_shell(envp, data->exit_status, data->first, *tmp);
	*tmp = ft_env_dup(shell->env);
	if (!shell)
	{
		data->exit_status = 0;
		free(str);
		return (NULL);
	}
	if (!start_parsing(str, data->exit_status, shell))
	{
		data->exit_status = 2;
		free(str);
		return (NULL);
	}
	return (shell);
}

void	loop(t_data *data, char **envp, t_env **tmp, char *str)
{
	t_shell	*shell;

	while (1)
	{
		handle_sig();
		str = readline("minishell> ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		handle_sigint(data);
		if (!*str)
		{
			free(str);
			continue ;
		}
		shell = shell_parsing(envp, data, str, tmp);
		if (!shell)
			continue ;
		end_shell(shell, tmp, str, data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	t_env	*tmp;
	char	*str;

	str = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->first = 0;
	data->exit_status = 0;
	tmp = NULL;
	(void)av;
	if (ac != 1)
		return (1);
	loop(data, envp, &tmp, str);
	free(data);
	rl_clear_history();
	free_env(tmp);
	return (0);
}
