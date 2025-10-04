/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:45:23 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/03 19:14:19 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	t_redir	*redir_tmp;
	t_cmd	*cmd_tmp;
	
	k = 0;
	i = 0;
	cmd_tmp = cmd;
	while (cmd_tmp)
	{
		j = 0;
		redir_tmp = cmd_tmp->redirect;
		printf("COMMANDE NBR : %d\n", i);
		while (cmd_tmp->args[j])
		{
			fprintf(stderr, "CMD ARGS [%d]: %s\n", j, cmd_tmp->args[j]);
			j++;
		}
		while (redir_tmp)
		{
			fprintf(stderr, "TYPE [%d]: %d\n", k, redir_tmp->type);
			fprintf(stderr, "FILE [%d]: %s\n", k, redir_tmp->file);
			k++;
			redir_tmp = redir_tmp->next;
		}
		i++;
		cmd_tmp = cmd_tmp->next;
	}
}

void	print_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (!token)
		return ;
	while (tmp)
	{
		printf("VALUE AU RANG [%d]: %s\n", i, tmp->value);
		printf("TYPE AU RANG [%d]: %d\n", i, (int)tmp->type);
		i++;
		tmp = tmp->next;
	}
	printf("FIN DE PRINT TOKEN\n\n");
}

