/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/26 17:22:02 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;	
	}
}

void	change_redir(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	tmp = tmp->next;
	tmp->redirect->type = REDIRR;
	tmp->redirect->next = NULL;
	//tmp = tmp->next;
	//tmp->redirect = NULL;
	//tmp = tmp->next;
	//tmp->redirect->type = REDIRL;
	//tmp->redirect->next->type = REDIRDR;
	//tmp->redirect->next->next = NULL;
	//tmp->next = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*line;
	int	exit_status;
	int	status;
	int	i;
	int	is_cmd;

	is_cmd = 1;
	(void)av;
	i = 0;
	if (ac != 1)
		return (1);
	shell = init_shell(envp);
	if (!shell)
		return (1);
	while (1)
	{
		//fprintf(stderr, "MON PID MAINNNNN EST : %d\n", getpid());
		i = 0;
		line = readline("minishell> ");
		//Cas de CTRL D : av et cmd = NULL parce que s'ils ont ete free a la boucle d'avant
		// Ca va segfault dans le free_shell de fin de main si ils n'ont pas ete mis a NULL;
		if (!line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			shell->line = NULL;
			printf("CTRL D\n");
			break;
		}
		if (*line)
			add_history(line);
		shell->line = ft_strdup(line);
		if (!shell->line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			shell->line = NULL;
			printf("shell->line strdup failed\n");
			break;
		}
		shell->av = ft_split(line, ' ');
		if (!shell->av)
		{
			free(line);
			shell->cmd = NULL;
			printf("shell->av split failed\n");
			continue ;
		}
		shell->cmd = init_cmd(shell->av);
		//change_redir(shell->cmd);
		if (!shell->cmd)
		{
			free(line);
			shell->cmd = NULL;
			shell->av = NULL;
			break;
		}
		shell->nbr_cmd = count_list(shell->cmd);
		start_exec(shell);
		while (i < shell->nbr_cmd)
		{
			waitpid(shell->pipe_infos->pid[i], &status, 2);
			i++;
		}
		/* while (shell->cmd)
		{
			if (is_builtin(shell->cmd->args[0]) && shell->nbr_cmd == 1)
				is_cmd = 0;
			start_exec(shell, i);
			free_move_cmd(shell->cmd);
			tmp = shell->cmd->next;
			free(shell->cmd);
			shell->cmd = tmp;
			if (is_cmd == 1)
				waitpid(shell->pipe_infos->pid[i], &status, 2);
			fprintf(stderr, "OK JE VAIS I++\n");	
			i++;
		} */
		//i = -1;
		//while (++i < shell->nbr_cmd)
		//	waitpid(shell->pipe_infos->pid[i], &status, 2);
		free(line);
		free_cmd(shell->cmd);
		free_split(shell->av);
		free(shell->line);
		// printf("%d\n", shell->exit_status);
	}
	if (shell->exit_status != 0)
	{
		exit_status = shell->exit_status;
		shell->av = NULL;
		shell->cmd = NULL;
		shell->line = NULL;
		free_shell(shell);
		return (exit_status);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}

