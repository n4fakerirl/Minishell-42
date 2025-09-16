/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:13:28 by lenakach          #+#    #+#             */
/*   Updated: 2025/09/16 11:51:10 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	opening(t_pipex *pipex, char **av, int ac)
{
	
	pipex->fd_infile = open(av[1], O_RDONLY, 0777);
	if (pipex->fd_infile < 0)
		perror("Infile not opening");
	pipex->fd_outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT,
			0777);
	if (pipex->fd_outfile < 0)
		perror("Outfile not opening");
} */

void	init_pipex_bonus(t_pipex *pipex)
{
	pipex->path = NULL;
	pipex->path_final = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd = NULL;
}


int	start_pipex(t_cmd *cmd)
{
	t_pipex	pipex;
	int		i;
	int		sortie;

	i = -1;
	init_pipex_bonus(&pipex);

	//UNE SEULE COMMANDE	
	//Sans redirection
	first_pipe(&pipex, cmd, envp);
	//inter_pipe(&pipex, av, ac, envp);
	//last_pipe(&pipex, av, ac, envp);
	while (++i < ac - 4)
		waitpid(pipex.pid[i], &sortie, 2);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		unlink(".heredoc_tmp");
	close_main(&pipex);
	return (WEXITSTATUS(sortie));
}
