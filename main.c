/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:58:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/22 17:53:30 by lenakach         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*line;
	int	exit_status;
	int	status;
	int	i;
	t_cmd	*tmp;

	(void)av;
	i = 0;
	if (ac != 1)
		return (1);
	shell = init_shell(envp);
	if (!shell)
		return (1);
	while (1)
	{
		printf("MON PID MAINNNNN EST : %d\n", getpid());
		i = 0;
		line = readline("minishell> ");
		//Cas de CTRL D : av et cmd = NULL parce que s'ils ont ete free a la boucle d'avant
		// Ca va segfault dans le free_shell de fin de main si ils n'ont pas ete mis a NULL;
		if (!line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			printf("CTRL D\n");
			break;
		}
		if (*line)
			add_history(line);
		shell->line = ft_strdup(line);
		//Protection du malloc du ft_strdup
		//Meme chose que cas CTRL D;shell->cmd
		if (!shell->line)
		{
			shell->av = NULL;
			shell->cmd = NULL;
			printf("shell->line strdup failed\n");
			break;
		}
		shell->av = ft_split(line, ' ');
		if (!shell->av)
		{
			free(line); //ne vas pas passer par le free(line) de fin de while, direct fin du main donc il faut free(line)
			shell->cmd = NULL; //si jamais il a ete free au tour d'avant, pour pas que ca segfault dans le free_shell
			//Pas besoin de shell->av = NULL puisqu'il est deja NULL dans cette condition
			printf("shell->av split failed\n");
			break;
		}
		shell->cmd = init_cmd(shell->av);
		if (!shell->cmd)
		{
			free(line);
			shell->cmd = NULL;
			shell->av = NULL;
			break;
		}
		shell->nbr_cmd = count_list(shell->cmd);
		while (shell->cmd)
		{
			printf("Etape 1 : start_exec au rang [%d]\n", i);
			start_exec(shell, i);
			free_move_cmd(shell->cmd);
			tmp = shell->cmd->next;
			free(shell->cmd);
			shell->cmd = tmp;
			i++;
		}
		i = -1;
		while (++i < shell->nbr_cmd)
			waitpid(shell->pipe_infos->pid[i], &status, 2);
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

