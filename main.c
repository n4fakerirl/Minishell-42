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

void	end_shell(t_shell *shell, char *str, t_data *data)
{
	t_env	*old_tmp;
	t_cmd	*tmp_cmd;

	shell->nbr_cmd = count_list(shell->cmd);
	start_exec(shell);
	old_tmp = data->tmp;
	data->tmp = ft_env_dup(shell->env);
	if (old_tmp)
		free_env(old_tmp);
	data->exit_status = shell->exit_status;
	free(str);
	tmp_cmd = shell->head_cmd;
	while (tmp_cmd)
	{
		if (tmp_cmd->here_doc > 2)
		{
			close(tmp_cmd->here_doc);
			tmp_cmd->here_doc = -1;
		}
		tmp_cmd = tmp_cmd->next;
	}
	free_shell(shell);
	if (data->first == 0)
		data->first = 1;
}

t_shell	*shell_parsing(char **envp, t_data *data, char *str)
{
	t_shell	*shell;

	shell = init_shell(envp, data->exit_status, data->first, data->tmp);
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

void	loop(t_data *data, char **envp, char *str, const char *prompt)
{
	t_shell	*shell;

	shell = NULL;
	while (1)
	{
		handle_sig();
		str = readline(prompt);
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
		shell = shell_parsing(envp, data, str);
		if (!shell)
			continue ;
		shell->data = data;
		end_shell(shell, str, data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	t_env		*tmp;
	char		*str;
	const char	*prompt = "minishell> ";

	str = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_malloc(), 1);
	ft_bzero(data, sizeof(t_data));
	tmp = NULL;
	data->tmp = tmp;
	(void)av;
	if (ac != 1)
		return (1);
	loop(data, envp, str, prompt);
	rl_clear_history();
	if (data->tmp)
		free_env(data->tmp);
	if (data)
		free(data);
	return (0);
}
